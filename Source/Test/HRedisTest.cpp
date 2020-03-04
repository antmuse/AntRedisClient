#include "HRedisTest.h"
#include "IAppLogger.h"
#include "CWorker.h"
#include "CWorkerCluster.h"
#include "CWorkerClusterZset.h"
#include <vector>
#include <stdio.h>

namespace irr {


bool list = false;
void AppListcallback(db::CRedisRequest* it, db::CRedisResponse* res) {
    res->show();
    list = true;
}

net::CNetConfig* AppCreateConfig() {
    net::CNetConfig* config = new net::CNetConfig();
    config->mMaxWorkThread = 5;
    config->mMaxFetchEvents = 128;
    config->mMaxContext = 16;
    config->mPollTimeout = 5;
    config->mSessionTimeout = 20000;
    config->check();
    config->print();
    return config;
}

void AppTestRedis(int max_threads) {
    net::CNetConfig* config = AppCreateConfig();
    net::CNetServiceTCP chub;
    chub.start(config);
    config->drop();

    net::CNetAddress addr("10.1.63.128", 5000);
    db::CRedisClientPool tRedisPool(&chub);
    tRedisPool.open(addr, 1, "123456", 0);

    std::vector<CWorker*> threads;
    for(int i = 0; i < max_threads; i++) {
        CWorker* thread = new CWorker(tRedisPool);
        threads.push_back(thread);
        thread->start();
    }


    db::CRedisRequest* con = new db::CRedisRequest();
    con->setCallback(AppListcallback);
    //con->setUserPointer(this);
    con->setClientPool(&tRedisPool);
    if(!con->lrange("web_Account1", sizeof("web_Account1") - 1, 0, -1)) {
        printf("redis get str failed\n");
    } else {
        while(!list) {
            CThread::sleep(100);
        }
    }
    con->drop();


    //CThread::sleep(10000);
    irr::c8 key = '\0';
    while('*' != key) {
        printf("@Please input [*] to quit");
        scanf("%c", &key);
        IAppLogger::log(ELOG_INFO, "AppRunEchoClient", "key=%c", key);
    }
    tRedisPool.close();
    std::vector<CWorker*>::iterator it = threads.begin();
    for(; it != threads.end(); ++it) {
        (*it)->stop();
        delete (*it);
    }
    chub.stop();
}

void AppTestRedisCluster(int max_threads) {
    net::CNetConfig* config = AppCreateConfig();
    net::CNetServiceTCP chub;
    chub.start(config);
    config->drop();

    db::CRedisClientCluster* cluster = new db::CRedisClientCluster(&chub);
    cluster->setPassword("10.1.63.126:5000", "123456");
    cluster->setPassword("10.1.63.126:5100", "123456");
    cluster->setPassword("10.1.63.127:5000", "123456");
    cluster->setPassword("10.1.63.127:5100", "123456");
    cluster->setPassword("10.1.63.128:5100", "123456");
    cluster->set("10.1.63.128:5000", 5, "123456");
    cluster->setMaxRedirect(2);
    cluster->setMaxTcp(5);
    cluster->open(false);

    std::vector<CWorkerCluster*> threads;
    for(int i = 0; i < max_threads; i++) {
        CWorkerCluster* thread = new CWorkerCluster(*cluster);
        threads.push_back(thread);
        thread->start();
    }

    //CThread::sleep(10000);
    irr::c8 key = '\0';
    while('*' != key) {
        printf("@Please input [*] to quit");
        scanf("%c", &key);
        IAppLogger::log(ELOG_INFO, "AppRunEchoClient", "key=%c", key);
    }
    cluster->close();
    std::vector<CWorkerCluster*>::iterator it = threads.begin();
    for(; it != threads.end(); ++it) {
        (*it)->stop();
        delete (*it);
    }
    chub.stop();
    delete cluster;
}

void AppTestRedisClusterZset(int max_threads) {
    net::CNetConfig* config = AppCreateConfig();
    net::CNetServiceTCP chub;
    chub.start(config);
    config->drop();

    db::CRedisClientCluster* cluster = new db::CRedisClientCluster(&chub);
    cluster->setPassword("10.1.63.126:5000", "123456");
    cluster->setPassword("10.1.63.126:5100", "123456");
    cluster->setPassword("10.1.63.127:5000", "123456");
    cluster->setPassword("10.1.63.127:5100", "123456");
    cluster->setPassword("10.1.63.128:5100", "123456");
    cluster->set("10.1.63.128:5000", 5, "123456");
    cluster->setMaxRedirect(2);
    cluster->setMaxTcp(5);
    cluster->open(false);

    std::vector<CWorkerClusterZset*> threads;
    for (int i = 0; i < max_threads; i++) {
        CWorkerClusterZset* thread = new CWorkerClusterZset(*cluster);
        threads.push_back(thread);
        thread->start();
    }

    //CThread::sleep(10000);
    irr::c8 key = '\0';
    while ('*' != key) {
        printf("@Please input [*] to quit");
        scanf("%c", &key);
        IAppLogger::log(ELOG_INFO, "AppRunEchoClient", "key=%c", key);
    }
    cluster->close();
    std::vector<CWorkerClusterZset*>::iterator it = threads.begin();
    for (; it != threads.end(); ++it) {
        (*it)->stop();
        delete (*it);
    }
    chub.stop();
    delete cluster;
}

}//irr
