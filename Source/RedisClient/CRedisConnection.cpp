#include "CRedisRequest.h"

namespace irr {
namespace db {


bool CRedisRequest::auth(const c8* passowrd) {
    if (nullptr == passowrd) {
        return false;
    }
    const c8* argv[2];
    argv[0] = "AUTH";
    argv[1] = passowrd;
    u32 lens[2];
    lens[0] = 4;
    lens[1] = static_cast<u32>(strlen(passowrd));
    return launch(2, argv, lens);
}

bool CRedisRequest::echo(const c8* msg) {
    if (nullptr == msg) {
        return false;
    }
    const c8* argv[2];
    argv[0] = "ECHO";
    argv[1] = msg;
    u32 lens[2];
    lens[0] = 4;
    lens[1] = static_cast<u32>(strlen(msg));
    return launch(2, argv, lens);
}

bool CRedisRequest::select(s32 dbID) {
    c8 dbstr[32];
    itoa(dbID, dbstr, 10);
    const c8* argv[2];
    argv[0] = "SELECT";
    argv[1] = dbstr;
    u32 lens[2];
    lens[0] = 6;
    lens[1] = static_cast<u32>(strlen(dbstr));
    return launch(2, argv, lens);
}

bool CRedisRequest::ping() {
    const c8* argv[1];
    argv[0] = "PING";
    u32 lens[1];
    lens[0] = 4;
    return launch(1, argv, lens);
}

bool CRedisRequest::quit() {
    const c8* argv[1];
    argv[0] = "QUIT";
    u32 lens[1];
    lens[0] = 4;
    return launch(1, argv, lens);
}


bool CRedisRequest::shutdown() {
    const c8* argv[1];
    argv[0] = "SHUTDOWN";
    u32 lens[1];
    lens[0] = 8;
    return launch(1, argv, lens);
}



} //namespace db {
} // namespace irr

