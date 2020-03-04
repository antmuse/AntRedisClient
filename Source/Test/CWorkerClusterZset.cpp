#include "CWorkerClusterZset.h"

namespace irr {


void AppRedisCallerZset(db::CRedisRequest* it, db::CRedisResponse* res) {
    CWorkerClusterZset* caller = reinterpret_cast<CWorkerClusterZset*>(it->getUserPointer());
    APP_ASSERT(caller);
    caller->callback(it, res);
}


CWorkerClusterZset::CWorkerClusterZset(db::CRedisClientCluster& tRedisPool) :
    mRunning(true),
    mFly(0),
    mRedisPool(tRedisPool) {
}


CWorkerClusterZset::~CWorkerClusterZset() {
}

void CWorkerClusterZset::callback(db::CRedisRequest* it, db::CRedisResponse* res) {
    u64 cnt = reinterpret_cast<u64>(it->getUserPointer());
    if(res->isError()) {
        printf("[item=%llu],", cnt);
    }
    res->show();
    AppAtomicDecrementFetch(&mFly);
}

void CWorkerClusterZset::run() {
    //return;
    const c8* keyname = "timed";
    const u32 keysz = strlen(keyname);
    c8 val[2048];
    c8 score[16];
    const c8* vals[2] = { score, val };
    u32 valsz[2];
    for(s32 i = 0; mRunning && i < 100; i++) {
        valsz[0] = snprintf(score, sizeof(score), "%d", i + 1);
        valsz[1] = snprintf(val, sizeof(val), "redvalue-index-%d", i + 1);
        //valsz[1] = sizeof(val);
        //val[valsz[1] + 1] = 'a';
        //val[valsz[1] + 2] = 0;
        //valsz[1] += 2;
        db::CRedisRequest* con = new db::CRedisRequest();
        con->setCallback(AppRedisCallerZset);
        con->setUserPointer(this);
        con->setClientCluster(&mRedisPool);
        if (!con->zadd(keyname, keysz, vals, valsz, 2)) {
            printf("redis set str failed\n");
        } else {
            AppAtomicIncrementFetch(&mFly);
        }
        con->drop();
    }
    printf("redis post set ok\n");

    CThread::sleep(1000);
    for(s32 i = 0; mRunning && i < 1; i++) {
        valsz[0] = snprintf(score, sizeof(score), "%d", i + 1);
        db::CRedisRequest* con = new db::CRedisRequest();
        con->setCallback(AppRedisCallerZset);
        con->setUserPointer(this);
        con->setClientCluster(&mRedisPool);
        if (!con->zrangebyscore(keyname, keysz, 0, 5, 0, true)) {
            printf("redis get str failed\n");
        } else {
            AppAtomicIncrementFetch(&mFly);
        }
        con->drop();
    }
    printf("redis post get ok\n");

    while(mFly != 0) {
        CThread::sleep(100);
    }
    printf("redis post thread exited\n");
}

void CWorkerClusterZset::start() {
    mThread.start(*this);
}

void CWorkerClusterZset::stop() {
    mRunning = false;
    mThread.join();
}


}//irr
