#include "CRedisClientPool.h"
#include "CRedisClient.h"
#include "IAppLogger.h"
#include "CMemoryHub.h"
#include "CRedisRequest.h"
#include "HAtomicOperator.h"


namespace irr {
namespace db {

void AppPoolCallback(CRedisRequest* it, CRedisResponse* res) {
    CRedisClientPool* pool = it->getClientPool();
    CRedisClient* nd = it->getClient();
    u64 flag = reinterpret_cast<u64>(it->getUserPointer()); //1=password, 2=select
    if (1 == flag && pool->getDatabaseID() > 0) {
        if (res->isOK()) {
            it->setUserPointer((void*)2);
            it->select(pool->getDatabaseID());
        } else {
            //password error
        }
        return;
    }
    it->setClient(nullptr);
    pool->delinkWaitNode(nd);
    pool->push(nd);
}

CRedisClientPool::CRedisClientPool(net::CNetServiceTCP* iServer) :
    mServer(iServer),
    mDatabaseID(0),
    mFlyCount(0),
    mRunning(false),
    mMaxTCP(3) {
    memset(mPassword, 0, sizeof(mPassword));
    mHub = new CMemoryHub();
}

CRedisClientPool::~CRedisClientPool() {
    bool run = true;
    CQueue2Way::SNode* nd;
    do {
        nd = mQueue.popNode(run, 0);
        if (nd) {
            deleteSession(reinterpret_cast<CRedisClient*>(nd->mValue));
        }
    } while (nd);
    do {
        nd = mQueueWait.popNode(run, 0);
        if (nd) {
            deleteSession(reinterpret_cast<CRedisClient*>(nd->mValue));
        }
    } while (nd);
    mHub->drop();
    mHub = nullptr;
}

CRedisClient* CRedisClientPool::createSession(void) {
    CRedisClient* conn = new CRedisClient(mServer, mRemoterAddr);
    conn->setPassword(mPassword);
    conn->setDatabaseID(mDatabaseID);
    conn->setPool(this, mHub);
    return conn;
}

void CRedisClientPool::deleteSession(CRedisClient* it) {
    if (it) {
        void* uper = it->getUserPointer();
        if (uper) {
            CQueue2Way::SNode* nd = reinterpret_cast<CQueue2Way::SNode*>(uper);
            delete nd;
        }
        it->close();
        delete it;
    }
}

void CRedisClientPool::open(const net::CNetAddress& serverIP, s32 maxTCP,
    const c8* passowrd, s32 dbID) {
    if (mRunning) {
        return;
    }
    mRunning = true;
    mRemoterAddr = serverIP;
    mDatabaseID = dbID;
    mMaxTCP = maxTCP;
    setPassword(passowrd);
    for (u64 i = 0; i < mMaxTCP; ++i) {
        CRedisClient* it = createSession();
        CQueue2Way::SNode* nd = new CQueue2Way::SNode();
        it->setUserPointer(nd);
        nd->mValue = it;
        mQueueWait.pushNode(nd);
        if (!it->open()) {
            mQueueWait.delinkNode(nd);
            deleteSession(it);
            IAppLogger::logError("redis", "fail to open connect,server=%s:%u",
                serverIP.getIPString(), serverIP.getPort());
        }
    }
}

void CRedisClientPool::delinkWaitNode(CRedisClient* it) {
    if (it) {
        CQueue2Way::SNode* uper = reinterpret_cast<CQueue2Way::SNode*>(it->getUserPointer());
        mQueueWait.delinkNode(uper);
        AppAtomicIncrementFetch(&mFlyCount);
    }
}

void CRedisClientPool::onConnect(CRedisClient* it, s32 status) {
    CQueue2Way::SNode* uper = reinterpret_cast<CQueue2Way::SNode*>(it->getUserPointer());
    if (uper) {
        if (0 == mPassword[0]) {
            if (getDatabaseID() <= 0) {
                mQueueWait.delinkNode(uper);
                push(it);
                return;
            }
        }
        CRedisRequest* con = new CRedisRequest();
        con->setClientPool(this);
        con->setClient(it);
        con->setCallback(AppPoolCallback);
        con->setUserPointer(this);
        if (0 == mPassword[0]) {
            con->setUserPointer((void*)2);
            con->select(getDatabaseID());
        } else {
            con->setUserPointer((void*)1);
            con->auth(mPassword);
        }
        //mQueue.pushNode(uper);
        con->drop();
    }
}


CRedisClient* CRedisClientPool::pop(u32 iWaitTime) {
    CQueue2Way::SNode* nd = mQueue.popNode(mRunning, iWaitTime);
    if (nd) {
        AppAtomicIncrementFetch(&mFlyCount);
        return reinterpret_cast<CRedisClient*>(nd->mValue);
    }
    return nullptr;
}

void CRedisClientPool::push(CRedisClient* it) {
    if (it) {
        CQueue2Way::SNode* uper = reinterpret_cast<CQueue2Way::SNode*>(it->getUserPointer());
        if (uper) {
            if (it->isDislinked()) {
                mQueueWait.pushNode(uper);
            } else {
                mQueue.pushNode(uper);
            }
            AppAtomicDecrementFetch(&mFlyCount);
        } else {
            //error
            APP_ASSERT(0);
        }
    }
}

void CRedisClientPool::setPassword(const c8* pass) {
    if (pass && *pass) {
        memcpy(mPassword, pass, core::min_(sizeof(mPassword) - 1, 1 + strlen(pass)));
    }
}

void CRedisClientPool::setDatabaseID(s32 dbnum) {
    if (dbnum > 0) {
        mDatabaseID = dbnum;
    }
}

void CRedisClientPool::close() {
    if (!mRunning) {
        return;
    }
    mRunning = false;
    while (0 != mFlyCount) {
        CThread::sleep(20);
    }

    bool run = true;
    CQueue2Way::SNode* nd;
    do {
        nd = mQueueWait.popNode(run, 0);
        mQueue.pushNode(nd);
    } while (nd);

    do {
        nd = mQueue.popNode(run, 0);
        mQueueWait.pushNode(nd);
        if (nd) {
            (reinterpret_cast<CRedisClient*>(nd->mValue))->close();
        }
    } while (nd);
}

} //namespace db {
} // namespace irr

