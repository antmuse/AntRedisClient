#include "CRedisClient.h"
#include "CLogger.h"
#include "IUtility.h"
#include "HAtomicOperator.h"

namespace app {
namespace db {

CRedisClient::CRedisClient(net::CNetServiceTCP* iServer,
    const net::CNetAddress& addr) :
    mPool(nullptr),
    mHub(nullptr),
    mResult(nullptr),
    mCMD(nullptr),
    mExitFlag(false),
    mServer(iServer),
    mServerAddress(addr),
    mDatabaseID(0),
    mConnectID(0),
    mTcpStatus(0) {
    memset(mPassWord, 0, sizeof(mPassWord));
}

CRedisClient::~CRedisClient() {
    while(4 != mTcpStatus) {
        CThread::sleep(20);
    }
    if(mResult) {
        mResult->clear();
        mHub->release(mResult);
        mResult = nullptr;
    }
}

s32 CRedisClient::onTimeout(u32 sessionID,
    const net::CNetAddress& local, const net::CNetAddress& remote) {
    //switch (mTcpStatus) {
    //case 1:
    //    break;
    //}
    return 0;
}

s32 CRedisClient::onConnect(u32 sessionID,
    const net::CNetAddress& local, const net::CNetAddress& remote) {
    APP_ASSERT(mConnectID == sessionID);
    mTcpStatus = 2;
    if(mResult) {
        mResult->clear();
    }
    if(mPool) {
        mPool->onConnect(this, mTcpStatus);
        return 0;
    }
    return 0;
}

s32 CRedisClient::onDisconnect(u32 sessionID,
    const net::CNetAddress& local, const net::CNetAddress& remote) {
    s32 status = mExitFlag ? 4 : 3;
    mConnectID = 0;
    if(mCMD) {
        if(mResult) {
            if(!mResult->isFinished()) {
                //mResult->clear();
                mResult->makeError("TCP:onDisconnect");
            }
        } else {
            mResult = new
            (reinterpret_cast<CRedisResponse*>(mHub->allocate(sizeof(CRedisResponse)))) CRedisResponse(*mHub);
            mResult->makeError("TCP:onDisconnect");
        }
        callback();
    }
    if(!mExitFlag) {
        CLogger::logInfo("redis", "CRedisClient::onDisconnect>>%s:%u",
            mServerAddress.getIPString(), mServerAddress.getPort());
        open();
    }
    mTcpStatus = status;
    return 0;
}

s32 CRedisClient::onSend(u32 sessionID, void* buffer, s32 size, s32 result) {
    if(0 != result) {
        CLogger::logInfo("redis", "CRedisClient::onSend>>send fail, buf size=%d", size);
        //if (mResult) {
        //    if (!mResult->isFinished()) {
        //        mResult->makeError("TCP:onSend");
        //    }
        //} else {
        //    mResult = new
        //    (reinterpret_cast<CRedisResponse*>(mHub->allocate(sizeof(CRedisResponse)))) CRedisResponse(*mHub);
        //    mResult->makeError("TCP:onSend");
        //}
        //callback();
        //if (!mExitFlag) {
        //    mServer->disconnect(mConnectID);
        //}
    }
    return 0;
}

s32 CRedisClient::onReceive(const net::CNetAddress& remote, u32 sessionID, void* buffer, s32 size) {
    if(nullptr == mResult) {
        mResult = new
        (reinterpret_cast<CRedisResponse*>(mHub->allocate(sizeof(CRedisResponse)))) CRedisResponse(*mHub);
    }
    const s8* cur = (s8*)(buffer);
    mResult->import(cur, size);
    if(mResult->isFinished()) {
        callback();
    }
    return 0;
}

void CRedisClient::callback() {
    CRedisRequest* cmd = mCMD;
    CRedisResponse* rst = mResult;
    mResult = nullptr;
    mCMD = nullptr;
    db::CRedisClientPool* pool = cmd->getClientPool();
    //db::CRedisClient* nd = cmd->getClient();
    APP_ASSERT(pool);
    if(rst->isError()) {
        s32 replay = (rst->isAsk() ? 2 : (rst->isMoved() ? 4 : 1));
        const s8* ipt = nullptr;
        u32 slot = cmd->getSlot();
        if(replay > 1) {
            ipt = rst->getStr()
                + (4 == replay ? sizeof("MOVED") : (2 == replay ? sizeof("ASK") : 0));
            slot = core::App10StrToU32(ipt, &ipt);
            ++ipt;
        }
        if(cmd->relaunch(slot, ipt, replay)) {
            if(pool) {
                pool->push(this);
            }
            rst->clear();
            cmd->drop();
            cmd = nullptr;
        }
    }
    if(cmd) {
        AppRedisCaller fun = cmd->getCallback();
        if(fun) {
            fun(cmd, rst);
        }
        if(AppPoolCallback != fun) {
            cmd->setClient(nullptr);
            if(pool) {
                pool->push(this);
            }
        }
        cmd->drop();
        rst->clear();
    }
    mHub->release(rst);
}

void CRedisClient::setPassword(const char* pass) {
    if(pass && pass[0]) {
        memcpy(mPassWord, pass, core::min_(sizeof(mPassWord) - 1, strlen(pass)));
    }
}

bool CRedisClient::open() {
    if(mConnectID > 0) {
        return true;
    }
    mTcpStatus = 1;
    mConnectID = mServer->connect(mServerAddress, this);
    if(0 == mConnectID) {
        mTcpStatus = 4;
        CLogger::logError("redis", "fail to connect redis server: %s:%u",
            mServerAddress.getIPString(), mServerAddress.getPort());
        return false;
    }
    return true;
}

void CRedisClient::close() {
    mExitFlag = true;
    if(mConnectID > 0) {
        mServer->disconnect(mConnectID);
    }
}

bool CRedisClient::isDislinked() const {
    return mConnectID == 0;
}

bool CRedisClient::sendRequest(const s8* buf, u32 iSize, CRedisCommand* it) {
    if(mCMD) {
        APP_ASSERT(0);
        return false;
    }
    mCMD = static_cast<CRedisRequest*>(it);
    mCMD->grab();
    if(iSize == mServer->send(mConnectID, buf, iSize)) {
        return true;
    }

    mCMD->drop();
    mCMD = nullptr;
    return false;
}


} //namespace db {
} // end namespace app

