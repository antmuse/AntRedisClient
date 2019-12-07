#pragma once

#include "CNetAddress.h"
#include "CNetService.h"
#include "CQueue2Way.h"

namespace irr {
class CMemoryHub;

namespace db {
class CRedisRequest;
class CRedisResponse;
class CRedisClient;

//init pool
void AppPoolCallback(CRedisRequest* it, CRedisResponse* res);

/**
 * @brief redis 连接池类
 * redis connection pool.
 */
class CRedisClientPool {
public:
    CRedisClientPool(net::CNetServiceTCP* iServer);

    virtual ~CRedisClientPool();

    const c8* getPassword()const {
        return mPassword;
    }

    /**
     * 在非集群模式下，本方法用来设置连接建立后所选择的db
     * in no-cluster mode, the method is used to select the db after
     * the connection is created
     * @param dbnum {int}
     * @return {CRedisClientPool&}
     */
    void setDatabaseID(s32 dbnum);

    /**
     * 获得本连接池所对应的db
     * get the current db of the connections pool
     * @return {int}
     */
    s32 getDatabaseID() const {
        return mDatabaseID;
    }

    /**
    * @param iWaitTime max wait time, in milliseconds.
    */
    CRedisClient* pop(u32 iWaitTime = 0xFFFFFFFF);

    void push(CRedisClient* it);

    void delinkWaitNode(CRedisClient* it);

    const net::CNetAddress& getRemoterAddr()const {
        return mRemoterAddr;
    }

    void onConnect(CRedisClient* it, s32 status);

    void open(const net::CNetAddress& serverIP, s32 maxTCP,
        const c8* passowrd, s32 dbID = 0);

    void close();

    CMemoryHub* getMemHub()const {
        return mHub;
    }

protected:
    CRedisClient* createSession(void);
    void deleteSession(CRedisClient* it);
    void setPassword(const c8* pass);

private:
    bool mRunning;
    c8 mPassword[64];
    s32 mDatabaseID;
    net::CNetAddress mRemoterAddr;
    net::CNetServiceTCP* mServer;
    s32 mMaxTCP;
    s32 mFlyCount; //poped but not pushed.
    CQueue2Way mQueue;
    CQueue2Way mQueueWait;  //wait auth,select
    CMemoryHub* mHub;
};

} //namespace db {
} // namespace irr

