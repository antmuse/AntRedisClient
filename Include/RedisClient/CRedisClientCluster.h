#pragma once

#include "AppMap.h"
#include "CNetAddress.h"
#include "CRedisClientPool.h"

namespace app {
namespace db {
class CRedisResponse;

/**
 * @brief redis cluster connection pool.
 */
class CRedisClientCluster {
public:
    CRedisClientCluster(net::CNetServiceTCP* iServer);

    virtual ~CRedisClientCluster();

    /**
    * @brief inner use only
    */
    void updateSlots(CRedisResponse* res);

    /**
    * @brief set a pool against to IP:Port
    */
    CRedisClientPool* set(const s8* ipport, u32 maxTCP, const s8* passowrd = nullptr);
    CRedisClientPool* set(const net::CNetAddress& addr, u32 maxTCP, const s8* passowrd = nullptr);

    const core::TMap<net::CNetAddress::ID, core::CString>& getAllPassword()const {
        return mPassword;
    }

    /**
    * @brief set password against to IP:Port
    *        it's suggest to set passwords of all cluster nodes before open CRedisClientCluster.
    */
    void setPassword(const s8* ipport, const s8* passowrd);
    void setPassword(const net::CNetAddress& addr, const s8* passowrd);

    bool getPassword(const net::CNetAddress::ID& id, core::CString& passowrd);
    
    void setMaxTcp(u32 it) {
        mMaxTCP = it;
    }

    u32 getMaxTcp() const {
        return mMaxTCP;
    }

    void setMaxRedirect(u32 it) {
        mMaxRedirect = it;
    }

    u32 getMaxRedirect() const {
        return mMaxRedirect;
    }

    void setMaxSlot(u32 it) {
        mMaxSlots = it < 16384 ? it : 16384;
    }

    u32 getMaxSlot() const {
        return mMaxSlots;
    }

    CRedisClientPool* getBySlot(u32 it);
    CRedisClientPool* getByAddress(const s8* iport);

    void setSlot(u32 pos, CRedisClientPool* it);

    void clearSlot(u32 it);

    bool open(bool updateSlots = false);

    void close();

    CMemoryHub* getMemHub()const {
        return mHub;
    }

protected:

private:
    //0=init,1=starting,2=got slots error,3=started
    volatile u32 mStatus;
    u32 mMaxRedirect; //limit of moved or ask
    u32 mMaxSlots;
    CRedisClientPool** mSlots;
    net::CNetServiceTCP* mServer;
    u32 mMaxTCP;
    CQueue2Way mQueue;
    CQueue2Way mQueueWait;  //wait auth,select
    CMemoryHub* mHub;
    CMutex mMutex;
    core::TMap<net::CNetAddress::ID, core::CString> mPassword;
    core::TMap<net::CNetAddress::ID, CRedisClientPool*> mAllPool;
};

} //namespace db {
} // namespace app

