#pragma once
#include "HConfig.h"
#include "CMemoryHub.h"
#include "CRedisResponse.h"
#include "CRedisClientPool.h"
#include "CRedisClientCluster.h"

namespace irr {
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

    //redirect: MOVED, ASK
    bool relaunch(u32 slot, const c8* ip);

    static u16 hashSlot(const c8* key, u64 len);

    static u16 hashSlot(const c8* key) {
        return hashSlot(key, strlen(key));
    }

protected:
    CMemoryHub* mHub;
    CRedisClientPool* mPool;
    AppRedisCaller mCallback;
    CRedisClient* mLink;
    CRedisClientCluster* mCluster;
    c8* mRequestBuf;
    u32 mRequestSize;
    u32 mRequestCount; //redirect times

    bool launch(u32 argc, const c8** argv, const u32* lens);

    bool launch(u32 slot, u32 argc, const c8** argv, const u32* lens);

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
} // namespace irr

