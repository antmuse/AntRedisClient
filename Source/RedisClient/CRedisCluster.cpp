#include "CRedisRequest.h"

namespace app {
namespace db {


bool CRedisRequest::clusterInfo() {
    const s8* argv[2];
    u32 lens[2];

    argv[0] = "CLUSTER";
    lens[0] = 7;

    argv[1] = "INFO";
    lens[1] = 4;

    return launch(2, argv, lens);
}

bool CRedisRequest::clusterNodes() {
    const s8* argv[2];
    u32 lens[2];

    argv[0] = "CLUSTER";
    lens[0] = 7;

    argv[1] = "NODES";
    lens[1] = 5;

    return launch(2, argv, lens);
}

bool CRedisRequest::clusterSlots() {
    const s8* argv[2];
    u32 lens[2];

    argv[0] = "CLUSTER";
    lens[0] = 7;

    argv[1] = "SLOTS";
    lens[1] = 5;

    return launch(2, argv, lens);
}

} //namespace db {
} // namespace app

