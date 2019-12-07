#pragma once

#include "INetEventer.h"
#include "CNetAddress.h"
#include "CNetService.h"
#include "CNetPacket.h"
#include "CRedisResponse.h"
#include "CRedisRequest.h"


namespace irr {
namespace db {
class CRedisClientPool;

class CRedisClient : public net::INetEventer {
public:
    CRedisClient(net::CNetServiceTCP* server, const net::CNetAddress& addr);

    ~CRedisClient(void);

    /**
    * @brief inner use only
    */
    void setUserPointer(void* it) {
        mUserPointer = it;
    }

    /**
    * @brief inner use only
    */
    void* getUserPointer()const {
        return mUserPointer;
    }

    virtual INetEventer* onAccept(const net::CNetAddress& local)override {
        return nullptr;
    }

    virtual s32 onTimeout(u32 sessionID,
        const net::CNetAddress& local, const net::CNetAddress& remote)override;

    virtual s32 onConnect(u32 sessionID,
        const net::CNetAddress& local, const net::CNetAddress& remote)override;

    virtual s32 onDisconnect(u32 sessionID,
        const net::CNetAddress& local, const net::CNetAddress& remote)override;

    virtual s32 onSend(u32 sessionID, void* buffer, s32 size, s32 result)override;

    virtual s32 onReceive(const net::CNetAddress& remote, u32 sessionID, void* buffer, s32 size)override;

    virtual s32 onLink(u32 sessionID,
        const net::CNetAddress& local, const net::CNetAddress& remote)override {
        return 0;
    }

    void setPassword(const char* pass);

    void setDatabaseID(s32 dbnum) {
        if (dbnum > 0) {
            mDatabaseID = dbnum;
        }
    }

    /**
     * 获得本连接所选择的 db
     * get db for the connection
     * @return {int}
     */
    s32 getDatabaseID() const {
        return mDatabaseID;
    }

    CRedisClientPool* getRedisPool() const {
        return mPool;
    }

    void setPool(CRedisClientPool* it, CMemoryHub* hub) {
        mPool = it;
        if (hub) {
            hub->grab();
            if (mHub) {
                mHub->drop();
            }
            mHub = hub;
        }
    }

    /**
     * 判断该网络连接对象是否已经关闭
     * check if the connection has been finish
     * @return {bool}
     */
    bool isDislinked() const;


    const net::CNetAddress& getServerAddress()const {
        return mServerAddress;
    }

    bool open();
    void close();

    bool sendRequest(const c8* buf, u32 iSize, CRedisCommand* it);

private:
    void* mUserPointer;
    CRedisRequest* mCMD;
    CRedisClientPool* mPool;
    net::CNetServiceTCP* mServer;
    net::CNetAddress mServerAddress;
    //net::CNetPacket mPack;
    u32 mConnectID;
    bool mExitFlag;
    //0=init, 1=post connect,2=connected, 3=disconnected
    s32 mTcpStatus;

    CSpinlock mLock;     //lock=busy, unlock=idle
    c8 mPassWord[32];
    s32 mDatabaseID;
    CMemoryHub* mHub;
    CRedisResponse* mResult;
    void callback();
};

} //namespace db {
} // end namespace irr

