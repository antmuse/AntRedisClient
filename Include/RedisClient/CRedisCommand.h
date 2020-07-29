#pragma once
#include "HConfig.h"
#include "CMemoryHub.h"
#include "CRedisResponse.h"
#include "CRedisClientPool.h"
#include "CRedisClientCluster.h"

namespace app {
namespace db {

class CRedisCommand {
public:
    CRedisCommand();
    ~CRedisCommand();

    /**
    * @brief thread safe
    */
    void grab();

    /**
    * @brief thread safe
    */
    void drop();

    void setClientPool(CRedisClientPool* it) {
        if (it) {
            mPool = it;
            setMemHub(mPool->getMemHub());
        }
    }

    void setClientCluster(CRedisClientCluster* it) {
        if (it) {
            mCluster = it;
            setMemHub(mCluster->getMemHub());
        }
    }

    CRedisClientPool* getClientPool()const {
        return mPool;
    }

    CRedisClientCluster* getCluster()const {
        return mCluster;
    }

    CRedisClient* getClient()const {
        return mLink;
    }

    void setClient(CRedisClient* it) {
        mLink = it;
    }

    void setCallback(AppRedisCaller it) {
        mCallback = it;
    }

    AppRedisCaller getCallback()const {
        return mCallback;
    }

    void setMemHub(CMemoryHub* it) {
        if (mHub) {
            return;
        }
        if (it) {
            it->grab();
            mHub = it;
        }
    }

    CMemoryHub* getMemHub()const {
        return mHub;
    }


    void setUserPointer(void* it) {
        mUserPointer = it;
    }

    void* getUserPointer()const {
        return mUserPointer;
    }

    /**
    * @brief redirect: MOVED, ASK, fix slot if MOVED.
    *        MOVED 866 172.21.16.4:6379
    *        ASK 866 172.21.16.4:6379
    *
    * @param itype 1=Error, 2=ASK, 4=MOVED
    */
    bool relaunch(u32 slot, const s8* ip, s32 itype);

    u16 hashSlot(const s8* key, u64 len);

    u16 hashSlot(const s8* key) {
        return hashSlot(key, strlen(key));
    }

    u16 getSlot()const {
        return mSlot;
    }

protected:
    CMemoryHub* mHub;
    CRedisClientPool* mPool;
    AppRedisCaller mCallback;
    CRedisClient* mLink;
    CRedisClientCluster* mCluster;
    s8* mRequestBuf;
    u32 mRequestSize;
    u32 mRequestCount; //relaunch times
    u16 mSlot;

    bool launch(u32 argc, const s8** argv, const u32* lens);

    bool launch(u32 slot, u32 argc, const s8** argv, const u32* lens);

    bool isClusterMode()const {
        return nullptr != mCluster;
    }

private:
    s32 mReferenceCount;
    void* mUserPointer;

    CRedisCommand(const CRedisCommand&) = delete;
    const CRedisCommand& operator=(const CRedisCommand&) = delete;
};


} //namespace db {
} // namespace app

