#include "CRedisCommand.h"
#include "CRedisClient.h"
#include "HAtomicOperator.h"
#include "CCheckCRC16.h"
#include "IAppLogger.h"

namespace irr {
namespace db {


CRedisCommand::CRedisCommand() :
    mReferenceCount(1),
    mCluster(nullptr),
    mPool(nullptr),
    mLink(nullptr),
    mHub(nullptr),
    mRequestBuf(nullptr),
    mRequestSize(0),
    mRequestCount(0),
    mUserPointer(nullptr),
    mCallback(nullptr) {
}

CRedisCommand::~CRedisCommand() {
    if (mRequestBuf) {
        mHub->release(mRequestBuf);
        mRequestBuf = nullptr;
        mRequestSize = 0;
    }
    mHub->drop();
    mHub = nullptr;
}


void CRedisCommand::grab() {
    APP_ASSERT(mReferenceCount > 0);
    AppAtomicIncrementFetch(&mReferenceCount);
}

void CRedisCommand::drop() {
    s32 ret = AppAtomicDecrementFetch(&mReferenceCount);
    APP_ASSERT(ret >= 0);
    if (0 == ret) {
        delete this;
    }
}

bool CRedisCommand::launch(u32 slot, u32 argc, const c8** argv, const u32* lens) {
    if (nullptr == mCluster) {
        APP_ASSERT(0);
        return false;
    }
    mPool = mCluster->getBySlot(slot);
    if (nullptr == mPool) {
        APP_ASSERT(0);
        return false;
    }
    mLink = mPool->pop();
    if (nullptr == mLink) {
        return false;
    }
    return launch(argc, argv, lens);
}

bool CRedisCommand::launch(u32 argc, const c8** argv, const u32* lens) {
    if (mRequestBuf) {
        mHub->release(mRequestBuf);
        mRequestBuf = nullptr;
        mRequestSize = 0;
    }
    CRedisClient* link = mLink;
    if (nullptr == link) {
        if (nullptr == mPool) {
            APP_ASSERT(0);
            return false;
        }
        link = mPool->pop();
        if (nullptr == link) {
            return false;
        }
        mLink = link;
    }
    u64 allsz = 13 + 13 * argc + 1; //0xFFFFFFFF ×î´ó10Î»
    for (u32 i = 0; i < argc; ++i) {
        allsz += lens[i];
    }
    c8* const buf = mHub->allocate(allsz);
    c8* curr = buf + snprintf(buf, allsz, "*%u\r\n", argc);
    for (u32 i = 0; i < argc; ++i) {
        curr += snprintf(curr, allsz - (curr - buf), "$%u\r\n", lens[i]);
        memcpy(curr, argv[i], lens[i]);
        curr += lens[i];
        *curr++ = '\r';
        *curr++ = '\n';
    }
    *curr = '\0';   //for debug: show str
    mRequestBuf = buf;
    mRequestSize = static_cast<u32>(curr - buf);
    bool ret = link->sendRequest(buf, mRequestSize, this);
    if (!ret) {
        mRequestBuf = nullptr;
        mHub->release(buf);
        if (mPool) {
            mPool->push(link);
        }
        mLink = nullptr;
    }
    mRequestCount = 1;
    return ret;
}

bool CRedisCommand::relaunch(u32 slot, const c8* iport) {
    if (mCluster) {
        if (mRequestCount > mCluster->getMaxRedirect()) {
            IAppLogger::logInfo("redis", "CRedisCommand::relaunch>>Redirect threshold=%u, launched=%u",
                mCluster->getMaxRedirect(), mRequestCount);
            return false;
        }
        mPool = mCluster->getByAddress(iport);
        if (mPool) {
            mCluster->setSlot(slot, mPool);
        }
        mLink = mPool->pop();
        if (nullptr == mLink) {
            return false;
        }
        bool ret = mLink->sendRequest(mRequestBuf, mRequestSize, this);
        if (!ret) {
            mPool->push(mLink);
            mLink = nullptr;
            return false;
        }
        ++mRequestCount;
        return true;
    }
    return false;
}

u16 CRedisCommand::hashSlot(const c8* key, u64 len) {
    if (key) {
        CCheckCRC16 crc;
        return crc.add(key, static_cast<u32>(len));
    }
    return 0;
}

} //namespace db {
} // namespace irr

