#include "CWorker.h"

namespace app {

void AppRedisPoolCallback(db::CRedisRequest* it, db::CRedisResponse* res) {
    CWorker* caller = reinterpret_cast<CWorker*>(it->getUserPointer());
    APP_ASSERT(caller);
    caller->callback(it, res);
}

CWorker::CWorker(db::CRedisClientPool& tRedisPool) :
    mRunning(true),
    mFly(0),
    mRedisPool(tRedisPool) {
}

CWorker::~CWorker() {
}

void CWorker::callback(db::CRedisRequest* it, db::CRedisResponse* res) {
    u64 cnt = reinterpret_cast<u64>(it->getUserPointer());
    if(res->isError()) {
        printf("[item=%llu],", cnt);
    }
    res->show();

    AppAtomicDecrementFetch(&mFly);
}

void CWorker::run() {
    //return;
    s8 key[128];
    s8 val[128];
    for(s32 i = 0; mRunning && i < 10; i++) {
        snprintf(key, sizeof(key), "tk%d", i + 1);
        snprintf(val, sizeof(val), "tv-by-pool-index-%d", i + 1);
        db::CRedisRequest* con = new db::CRedisRequest();
        con->setCallback(AppRedisPoolCallback);
        con->setUserPointer(this);
        con->setClientPool(&mRedisPool);
        /*if (!con->ping(reinterpret_cast<void*>(i + 1))) {
            printf("redis ping failed\n");
        }*/
        if(!con->set(key, val)) {
            printf("redis set str failed\n");
        } else {
            AppAtomicIncrementFetch(&mFly);
        }
        con->drop();
    }

    CThread::sleep(1000);

    for(s32 i = 0; mRunning && i < 10; i++) {
        snprintf(key, sizeof(key), "tk%d", i + 1);
        db::CRedisRequest* con = new db::CRedisRequest();
        con->setCallback(AppRedisPoolCallback);
        con->setUserPointer(this);
        con->setClientPool(&mRedisPool);
        if(con->get(key)) {
            AppAtomicIncrementFetch(&mFly);
            db::CRedisRequest* con2 = new db::CRedisRequest();
            con2->setCallback(AppRedisPoolCallback);
            con2->setUserPointer(this);
            con2->setClientPool(&mRedisPool);
            if(con2->expire(key, 60)) {
                AppAtomicIncrementFetch(&mFly);
            } else {
                printf("redis expire failed\n");
            }
            con2->drop();
        } else {
            printf("redis get str failed\n");
        }
        con->drop();
    }

    printf("redis post thread exit...\n");
    while(mFly != 0) {
        CThread::sleep(100);
    }
    printf("redis post thread exited\n");
}

void CWorker::start() {
    mThread.start(*this);
}
void CWorker::stop() {
    mRunning = false;
    mThread.join();
}



}//irr
