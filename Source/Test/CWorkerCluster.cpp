#include "CWorkerCluster.h"

namespace app {


void AppRedisClusterCallback(db::CRedisRequest* it, db::CRedisResponse* res) {
    CWorkerCluster* caller = reinterpret_cast<CWorkerCluster*>(it->getUserPointer());
    APP_ASSERT(caller);
    caller->callback(it, res);
}


CWorkerCluster::CWorkerCluster(db::CRedisClientCluster& tRedisPool) :
    mRunning(true),
    mFly(0),
    mRedisPool(tRedisPool) {
}


CWorkerCluster::~CWorkerCluster() {
}

void CWorkerCluster::callback(db::CRedisRequest* it, db::CRedisResponse* res) {
    u64 cnt = reinterpret_cast<u64>(it->getUserPointer());
    if(res->isError()) {
        printf("[item=%llu],", cnt);
    }
    res->show();
    AppAtomicDecrementFetch(&mFly);
}

void CWorkerCluster::run() {
    //return;
    s8 key[128];
    s8 val[128];
    for(s32 i = 0; mRunning && i < 1000; i++) {
        snprintf(key, sizeof(key), "tk%d", i + 1);
        snprintf(val, sizeof(val), "redvalue-index-%d", i + 1);
        db::CRedisRequest* con = new db::CRedisRequest();
        con->setCallback(AppRedisClusterCallback);
        con->setUserPointer(this);
        con->setClientCluster(&mRedisPool);
        if(!con->set(key, val)) {
            printf("redis set str failed\n");
        } else {
            AppAtomicIncrementFetch(&mFly);
        }
        con->drop();
    }
    printf("redis post set ok\n");

    CThread::sleep(1000);
    for(s32 i = 0; mRunning && i < 1000; i++) {
        snprintf(key, sizeof(key), "tk%d", i + 1);
        db::CRedisRequest* con = new db::CRedisRequest();
        con->setCallback(AppRedisClusterCallback);
        con->setUserPointer(this);
        con->setClientCluster(&mRedisPool);
        if(con->get(key)) {
            AppAtomicIncrementFetch(&mFly);
            db::CRedisRequest* con2 = new db::CRedisRequest();
            con2->setCallback(AppRedisClusterCallback);
            con2->setUserPointer(this);
            con2->setClientCluster(&mRedisPool);
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
    printf("redis post get ok\n");

    while(mFly != 0) {
        CThread::sleep(100);
    }
    printf("redis post thread exited\n");
}

void CWorkerCluster::start() {
    mThread.start(*this);
}

void CWorkerCluster::stop() {
    mRunning = false;
    mThread.join();
}


}//irr
