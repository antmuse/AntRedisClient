#pragma once
#include "HConfig.h"

namespace app {

void AppTestRedis(int max_threads);

void AppTestRedisCluster(int max_threads);

void AppTestRedisClusterZset(int max_threads);

}//irr
