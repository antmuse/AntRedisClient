#include "CRedisCommand.h"
#include "CRedisClient.h"
#include "HAtomicOperator.h"
#include "CCheckCRC.h"
#include "CLogger.h"

namespace app {
namespace db {


CRedisCommand::CRedisCommand() :
    mSlot(0),
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
    if(mRequestBuf) {
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
    if(0 == ret) {
        delete this;
    }
}

bool CRedisCommand::launch(u32 slot, u32 argc, const s8** argv, const u32* lens) {
    if(nullptr == mCluster) {
        APP_ASSERT(0);
        return false;
    }
    mPool = mCluster->getBySlot(slot);
    if(nullptr == mPool) {
        CLogger::logError("redis", "CRedisCommand::launch>>can't get pool, slot=%u", slot);
        APP_ASSERT(0);
        return false;
    }
    mLink = mPool->pop();
    if(nullptr == mLink) {
        return false;
    }
    return launch(argc, argv, lens);
}

bool CRedisCommand::launch(u32 argc, const s8** argv, const u32* lens) {
    if(mRequestBuf) {
        mHub->release(mRequestBuf);
        mRequestBuf = nullptr;
        mRequestSize = 0;
    }
    CRedisClient* link = mLink;
    if(nullptr == link) {
        if(nullptr == mPool) {
            APP_ASSERT(0);
            return false;
        }
        link = mPool->pop();
        if(nullptr == link) {
            return false;
        }
        mLink = link;
    }
    u64 allsz = 13 + 13 * argc + 1; //0xFFFFFFFF 最大10位
    for(u32 i = 0; i < argc; ++i) {
        allsz += lens[i];
    }
    s8* const buf = mHub->allocate(allsz);
    s8* curr = buf + snprintf(buf, allsz, "*%u\r\n", argc);
    for(u32 i = 0; i < argc; ++i) {
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
    if(!ret) {
        mRequestBuf = nullptr;
        mHub->release(buf);
        if(mPool) {
            mPool->push(link);
        }
        mLink = nullptr;
    }
    mRequestCount = 1;
    return ret;
}

bool CRedisCommand::relaunch(u32 slot, const s8* iport, s32 itype) {
    ++mRequestCount;
    if(mCluster) {
        if(mRequestCount > mCluster->getMaxRedirect()) {
            CLogger::logInfo("redis", "CRedisCommand::relaunch>>Redirect threshold=%u, launched=%u",
                mCluster->getMaxRedirect(), mRequestCount);
            return false;
        }
        //重定向或原槽位上重试
        mPool = itype > 1 ? mCluster->getByAddress(iport) : mCluster->getBySlot(slot);
        if(!mPool) {
            CLogger::logError("redis", "CRedisCommand::relaunch>>can't get pool, slot=%u, IP=%s", slot, iport ? iport : "");
            return false;
        }
        if(4 == itype) {
            mCluster->setSlot(slot, mPool);
        }
    } else {
        //非集群模式下重试
        if(!mPool) {
            CLogger::logError("redis", "CRedisCommand::relaunch>>can't retry, slot=%u, IP=%s", slot, iport ? iport : "");
            return false;
        }
        if(mRequestCount > mPool->getMaxRetry()) {
            CLogger::logInfo("redis", "CRedisCommand::relaunch>>more retry=%u, max=%u", mRequestCount, mPool->getMaxRetry());
            return false;
        }
    }

    mLink = mPool->pop();
    if(nullptr == mLink) {
        return false;
    }
    bool ret = mLink->sendRequest(mRequestBuf, mRequestSize, this);
    if(!ret) {
        mPool->push(mLink);
        mLink = nullptr;
        return false;
    }
    return true;
}

u16 CRedisCommand::hashSlot(const s8* key, u64 len) {
    if(key) {
        CCheckCRC16 crc;
        mSlot = crc.add(key, static_cast<u32>(len));
        return mSlot;
    }
    mSlot = 0;
    return 0;
}

} //namespace db {
} // namespace app

