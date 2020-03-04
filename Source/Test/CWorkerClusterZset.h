#pragma once

#include "CThread.h"
#include "CRedisClientPool.h"
#include "IAppLogger.h"
#include "CRedisRequest.h"
#include "CRedisClientCluster.h"

namespace irr {


class CWorkerClusterZset : public IRunnable {
public:
    CWorkerClusterZset(db::CRedisClientCluster& tRedisPool);

    virtual ~CWorkerClusterZset();

    void callback(db::CRedisRequest* it, db::CRedisResponse* res);

    virtual void run()override;

    void start();

    void stop();

private:
    db::CRedisClientCluster& mRedisPool;
    CThread mThread;
    bool mRunning;
    s32 mFly;
};

}//irr
