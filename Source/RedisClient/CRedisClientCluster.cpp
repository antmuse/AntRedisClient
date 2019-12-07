#include "CRedisClientCluster.h"
#include "CRedisClient.h"
#include "IAppLogger.h"
#include "CMemoryHub.h"
#include "CRedisRequest.h"


namespace irr {
namespace db {

void AppClusterCallback(CRedisRequest* it, CRedisResponse* res) {
    CRedisClientCluster* cls = it->getCluster();
    //CRedisClient* nd = it->getClient();
    cls->updateSlots(res);
}

CRedisClientCluster::CRedisClientCluster(net::CNetServiceTCP* iServer) :
    mMaxSlots(16384),
    mServer(iServer),
    mStatus(0),
    mMaxRedirect(3),
    mMaxTCP(3) {
    mHub = new CMemoryHub();
    mSlots = new CRedisClientPool*[mMaxSlots];
    memset(mSlots, 0, mMaxSlots * sizeof(CRedisClientPool*));
}

CRedisClientCluster::~CRedisClientCluster() {
    core::map<net::CNetAddress::ID, CRedisClientPool*>::Iterator nd = mAllPool.getIterator();
    while (!nd.atEnd()) {
        CRedisClientPool* pool = nd->getValue();
        delete pool;
        nd++;
    }

    mHub->drop();
    mHub = nullptr;

    delete[] mSlots;
    mSlots = nullptr;
}

void CRedisClientCluster::updateSlots(CRedisResponse* res) {
    if (res->isError()) {
        mStatus = 2;
        APP_ASSERT(0);
        return;
    }
    res->show();
    net::CNetAddress addr;
    c8* ids;
    for (u32 i = 0; i < res->mAllocated; ++i) {
        CRedisResponse* ndj = res->getResult(i);
        u64 slot1 = ndj->getResult(0)->getS64();
        u64 slot2 = ndj->getResult(1)->getS64();
        CRedisResponse* ndk = ndj->getResult(2);
        addr.setIP(ndk->getResult(0)->getStr());
        addr.setPort((u16)ndk->getResult(1)->getS64());
        ids = ndk->getResult(2)->getStr();
        CRedisClientPool* pool = set(addr, mMaxTCP, nullptr);
        if (pool && slot2 < mMaxSlots) {
            CAutoLock ak(mMutex);
            for (; slot1 <= slot2; ++slot1) {
                mSlots[slot1] = pool;
            }
        } else {
            APP_ASSERT(0);
        }
    }
    mStatus = 3;
}

void CRedisClientCluster::setPassword(const c8* ipport, const c8* passowrd) {
    if (nullptr == ipport) {
        return;
    }
    net::CNetAddress addr;
    addr.setIPort(ipport);
    setPassword(addr, passowrd);
}

void CRedisClientCluster::setPassword(const net::CNetAddress& addr, const c8* passowrd) {
    if (nullptr == passowrd) {
        return;
    }
    core::stringc pass(passowrd);

    CAutoLock ak(mMutex);
    mPassword.insert(addr.getID(), pass);
}

bool CRedisClientCluster::getPassword(const net::CNetAddress::ID& ipport, core::stringc& passowrd) {
    CAutoLock ak(mMutex);
    core::map<net::CNetAddress::ID, core::stringc>::Node* nd =
        mPassword.find(ipport);
    if (nullptr == nd) {
        return false;
    }
    passowrd = nd->getValue();
    return true;
}

CRedisClientPool* CRedisClientCluster::set(const c8* ipport, u32 maxTCP, const c8* passowrd) {
    if (nullptr == ipport) {
        return nullptr;
    }
    net::CNetAddress addr;
    addr.setIPort(ipport);
    return set(addr, maxTCP, passowrd);
}

CRedisClientPool* CRedisClientCluster::set(const net::CNetAddress& addr, u32 maxTCP, const c8* passowrd) {
    maxTCP = core::clamp(maxTCP, 1U, mMaxTCP);

    CAutoLock ak(mMutex);

    core::map<net::CNetAddress::ID, CRedisClientPool*>::Node* nd = mAllPool.find(addr.getID());
    if (nd) {
        return nd->getValue();
    }

    CRedisClientPool* pool = new CRedisClientPool(mServer);
    if (!mAllPool.insert(addr.getID(), pool)) {
        delete pool;
        return nullptr;
    }

    core::stringc pass(passowrd);
    if (nullptr == passowrd) {
        if (!getPassword(addr.getID(), pass)) {
            return nullptr;
        }
    } else {
        setPassword(addr, passowrd);
    }
    pool->open(addr, maxTCP, pass.c_str(), 0);

    if (1 == mAllPool.size()) {
        for (u32 i = 0; i < mMaxSlots; ++i) {
            mSlots[i] = pool;
        }
    }
    return pool;
}

bool CRedisClientCluster::open(bool updateSlots) {
    if (0 != mStatus) {
        return true;
    }
    //CAutoLock ak(mMutex);

    if (0 == mAllPool.size()) {
        return false;
    }
    if (updateSlots) {
        CRedisClientPool* pool = mAllPool.getIterator().getNode()->getValue();
        mStatus = 1;

        CRedisRequest* cmd = new CRedisRequest();
        cmd->setCallback(AppClusterCallback);
        cmd->setClientPool(pool);
        cmd->setClientCluster(this);
        //cmd->setUserPointer(this);
        cmd->clusterSlots();
        cmd->drop();
        for (u32 i = 0; i < 10 * 1000 && 3 != mStatus; i += 100) {
            CThread::sleep(100);
        }
        return 3 == mStatus;
    }

    mStatus = 3;
    return true;
}


void CRedisClientCluster::close() {
    CAutoLock ak(mMutex);
    if (!mStatus) {
        return;
    }
    mStatus = false;
    core::map<net::CNetAddress::ID, CRedisClientPool*>::Iterator nd = mAllPool.getIterator();
    while (!nd.atEnd()) {
        CRedisClientPool* pool = nd->getValue();
        pool->close();
        nd++;
    }
}

void CRedisClientCluster::clearSlot(u32 it) {
    if (it < mMaxSlots) {
        CAutoLock ak(mMutex);
        mSlots[it] = nullptr;
    }
}


void CRedisClientCluster::setSlot(u32 pos, CRedisClientPool* it) {
    if (it && pos < mMaxSlots) {
        CAutoLock ak(mMutex);
        //pos = pos%mMaxSlots;
        mSlots[pos] = it;
    }
}


CRedisClientPool* CRedisClientCluster::getBySlot(u32 it) {
    it = it%mMaxSlots;

    CAutoLock ak(mMutex);

    if (nullptr == mSlots[it]) {
        return nullptr;
    }
    CRedisClientPool* ret = mSlots[it];
    return ret;
}

CRedisClientPool* CRedisClientCluster::getByAddress(const c8* iport) {
    if (nullptr == iport) {
        return nullptr;
    }
    net::CNetAddress addr;
    addr.setIPort(iport);
    return set(addr, mMaxTCP, nullptr);
}

} //namespace db {
} // namespace irr

