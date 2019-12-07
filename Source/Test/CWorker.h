#pragma once

#include "CThread.h"
#include "IAppLogger.h"
#include "CRedisRequest.h"
#include "CRedisClientPool.h"

namespace irr {


class CWorker : public IRunnable {
public:
    CWorker(db::CRedisClientPool& tRedisPool);

    virtual ~CWorker();

    void callback(db::CRedisRequest* it, db::CRedisResponse* res);

    virtual void run()override;

    void start();

    void stop();

private:
    db::CRedisClientPool& mRedisPool;
    CThread mThread;
    bool mRunning;
    s32 mFly;
};

}//irr
