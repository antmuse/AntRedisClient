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

bool CRedisRequest::save() {
    const u32 cnt = 1;
    const c8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "SAVE";
    lens[0] = sizeof("SAVE") - 1;
    return launch(cnt, argv, lens);
}


bool CRedisRequest::bgsave() {
    const u32 cnt = 1;
    const c8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "BGSAVE";
    lens[0] = sizeof("BGSAVE") - 1;
    return launch(cnt, argv, lens);
}


bool CRedisRequest::bgrewriteaof() {
    const u32 cnt = 1;
    const c8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "BGREWRITEAOF";
    lens[0] = sizeof("BGREWRITEAOF") - 1;
    return launch(cnt, argv, lens);
}


bool CRedisRequest::lastsave() {
    const u32 cnt = 1;
    const c8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "LASTSAVE";
    lens[0] = sizeof("LASTSAVE") - 1;
    return launch(cnt, argv, lens);
}


} //namespace db {
} // namespace irr

