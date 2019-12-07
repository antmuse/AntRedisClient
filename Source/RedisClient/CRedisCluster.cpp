#include "CRedisRequest.h"

namespace irr {
namespace db {


bool CRedisRequest::clusterInfo() {
    const c8* argv[2];
    u32 lens[2];

    argv[0] = "CLUSTER";
    lens[0] = 7;

    argv[1] = "INFO";
    lens[1] = 4;

    return launch(2, argv, lens);
}

bool CRedisRequest::clusterNodes() {
    const c8* argv[2];
    u32 lens[2];

    argv[0] = "CLUSTER";
    lens[0] = 7;

    argv[1] = "NODES";
    lens[1] = 5;

    return launch(2, argv, lens);
}

bool CRedisRequest::clusterSlots() {
    const c8* argv[2];
    u32 lens[2];

    argv[0] = "CLUSTER";
    lens[0] = 7;

    argv[1] = "SLOTS";
    lens[1] = 5;

    return launch(2, argv, lens);
}

} //namespace db {
} // namespace irr

