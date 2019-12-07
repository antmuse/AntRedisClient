#include "CRedisRequest.h"
#include <string>

namespace irr {
namespace db {

bool CRedisRequest::del(const c8* key) {
    return del(key, static_cast<u32>(strlen(key)));
}

bool CRedisRequest::del(const c8* key, u32 keyLen) {
    const u32 cnt = 2;
    const c8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "DEL";
    lens[0] = sizeof("DEL") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::unlink(const c8* key) {
    return unlink(key, static_cast<u32>(strlen(key)));
}

bool CRedisRequest::unlink(const c8* key, u32 keyLen) {
    const u32 cnt = 2;
    const c8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "UNLINK";
    lens[0] = sizeof("UNLINK") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::pttl(const c8* key) {
    return pttl(key, static_cast<u32>(strlen(key)));
}

bool CRedisRequest::pttl(const c8* key, u32 keyLen) {
    const u32 cnt = 2;
    const c8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "PTTL";
    lens[0] = sizeof("PTTL") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::ttl(const c8* key) {
    return ttl(key, static_cast<u32>(strlen(key)));
}

bool CRedisRequest::ttl(const c8* key, u32 keyLen) {
    const u32 cnt = 2;
    const c8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "TTL";
    lens[0] = sizeof("TTL") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::type(const c8* key) {
    return type(key, static_cast<u32>(strlen(key)));
}

bool CRedisRequest::type(const c8* key, u32 keyLen) {
    const u32 cnt = 2;
    const c8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "TYPE";
    lens[0] = sizeof("TYPE") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::dump(const c8* key) {
    return dump(key, static_cast<u32>(strlen(key)));
}

bool CRedisRequest::dump(const c8* key, u32 keyLen) {
    const u32 cnt = 2;
    const c8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "DUMP";
    lens[0] = sizeof("DUMP") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}


bool CRedisRequest::keys(const c8* key) {
    return keys(key, static_cast<u32>(strlen(key)));
}

bool CRedisRequest::keys(const c8* key, u32 keyLen) {
    const u32 cnt = 2;
    const c8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "KEYS";
    lens[0] = sizeof("KEYS") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::pexpire(const c8* key, u32 timeout) {
    return pexpire(key, static_cast<u32>(strlen(key)), timeout);
}

bool CRedisRequest::pexpire(const c8* key, u32 keyLen, u32 timeout) {
    const u32 cnt = 3;
    const c8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "PEXPIRE";
    lens[0] = sizeof("PEXPIRE") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    c8 buf[16];
    snprintf(buf, sizeof(buf), "%u", timeout);
    argv[2] = buf;
    lens[2] = (u32)strlen(buf);

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::move(const c8* key, u32 destDB) {
    return move(key, static_cast<u32>(strlen(key)), destDB);
}

bool CRedisRequest::move(const c8* key, u32 keyLen, u32 destDB) {
    const u32 cnt = 3;
    const c8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "MOVE";
    lens[0] = sizeof("MOVE") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    c8 buf[16];
    snprintf(buf, sizeof(buf), "%u", destDB);
    argv[2] = buf;
    lens[2] = (u32)strlen(buf);

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::persist(const c8* key) {
    return persist(key, static_cast<u32>(strlen(key)));
}

bool CRedisRequest::persist(const c8* key, u32 keyLen) {
    const u32 cnt = 2;
    const c8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "PERSIST";
    lens[0] = sizeof("PERSIST") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::objectRefcount(const c8* key) {
    return objectRefcount(key, static_cast<u32>(strlen(key)));
}

bool CRedisRequest::objectRefcount(const c8* key, u32 keyLen) {
    const u32 cnt = 3;
    const c8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "OBJECT";
    lens[0] = sizeof("OBJECT") - 1;

    argv[1] = "REFCOUNT";
    lens[1] = sizeof("REFCOUNT") - 1;

    argv[2] = key;
    lens[2] = keyLen;

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::objectEncoding(const c8* key) {
    return objectEncoding(key, static_cast<u32>(strlen(key)));
}

bool CRedisRequest::objectEncoding(const c8* key, u32 keyLen) {
    const u32 cnt = 3;
    const c8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "OBJECT";
    lens[0] = sizeof("OBJECT") - 1;

    argv[1] = "ENCODING";
    lens[1] = sizeof("ENCODING") - 1;

    argv[2] = key;
    lens[2] = keyLen;

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::objectIdletime(const c8* key) {
    return objectIdletime(key, static_cast<u32>(strlen(key)));
}

bool CRedisRequest::objectIdletime(const c8* key, u32 keyLen) {
    const u32 cnt = 3;
    const c8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "OBJECT";
    lens[0] = sizeof("OBJECT") - 1;

    argv[1] = "IDLETIME";
    lens[1] = sizeof("IDLETIME") - 1;

    argv[2] = key;
    lens[2] = keyLen;

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::exists(const c8* key) {
    return exists(key, static_cast<u32>(strlen(key)));
}

bool CRedisRequest::exists(const c8* key, u32 keyLen) {
    const u32 cnt = 2;
    const c8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "EXISTS";
    lens[0] = sizeof("EXISTS") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::expire(const c8* key, u32 timeout) {
    return expire(key, static_cast<u32>(strlen(key)), timeout);
}

bool CRedisRequest::expire(const c8* key, u32 keyLen, u32 timeout) {
    const u32 cnt = 3;
    const c8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "EXPIRE";
    lens[0] = sizeof("EXPIRE") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    c8 buf[16];
    snprintf(buf, sizeof(buf), "%u", timeout);
    argv[2] = buf;
    lens[2] = (u32)strlen(buf);

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::expireat(const c8* key, s64 timeout) {
    return expireat(key, static_cast<u32>(strlen(key)), timeout);
}

bool CRedisRequest::expireat(const c8* key, u32 keyLen, s64 timeout) {
    const u32 cnt = 3;
    const c8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "EXPIREAT";
    lens[0] = sizeof("EXPIREAT") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    c8 buf[24];
    snprintf(buf, sizeof(buf), "%lld", timeout);
    argv[2] = buf;
    lens[2] = (u32)strlen(buf);

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::pexpireat(const c8* key, s64 timeout) {
    return pexpireat(key, static_cast<u32>(strlen(key)), timeout);
}

bool CRedisRequest::pexpireat(const c8* key, u32 keyLen, s64 timeout) {
    const u32 cnt = 3;
    const c8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "PEXPIREAT";
    lens[0] = sizeof("PEXPIREAT") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    c8 buf[24];
    snprintf(buf, sizeof(buf), "%lld", timeout);
    argv[2] = buf;
    lens[2] = (u32)strlen(buf);

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::randomkey() {
    const u32 cnt = 1;
    const c8* argv[cnt];

    u32 lens[cnt];
    argv[0] = "RANDOMKEY";
    lens[0] = sizeof("RANDOMKEY") - 1;

    return launch(cnt, argv, lens);
}

bool CRedisRequest::rename(const c8* key1, const c8* key2) {
    return rename(key1, static_cast<u32>(strlen(key1)), key2, static_cast<u32>(strlen(key2)));
}

bool CRedisRequest::rename(const c8* key1, u32 keyLen1, const c8* key2, u32 keyLen2) {
    const u32 cnt = 3;
    const c8* argv[cnt];

    u32 lens[cnt];
    argv[0] = "RENAME";
    lens[0] = sizeof("RENAME") - 1;

    argv[1] = key1;
    lens[1] = keyLen1;

    argv[2] = key2;
    lens[2] = keyLen2;

    if (isClusterMode()) {
        return launch(hashSlot(key1, keyLen1), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::renamenx(const c8* key1, const c8* key2) {
    return renamenx(key1, static_cast<u32>(strlen(key1)), key2, static_cast<u32>(strlen(key2)));
}

bool CRedisRequest::renamenx(const c8* key1, u32 keyLen1, const c8* key2, u32 keyLen2) {
    const u32 cnt = 3;
    const c8* argv[cnt];

    u32 lens[cnt];
    argv[0] = "RENAMENX";
    lens[0] = sizeof("RENAMENX") - 1;

    argv[1] = key1;
    lens[1] = keyLen1;

    argv[2] = key2;
    lens[2] = keyLen2;

    if (isClusterMode()) {
        return launch(hashSlot(key1, keyLen1), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::restore(const c8* key1, u32 keyLen1, const c8* key2, u32 keyLen2, s32 ttl, bool replace) {
    const u32 cnt = 5;
    const c8* argv[cnt];

    u32 lens[cnt];
    argv[0] = "RESTORE";
    lens[0] = sizeof("RESTORE") - 1;

    argv[1] = key1;
    lens[1] = keyLen1;

    c8 buf[16];
    snprintf(buf, sizeof(buf), "%d", ttl);
    argv[2] = buf;
    lens[2] = (u32)strlen(buf);

    argv[3] = key2;
    lens[3] = keyLen2;

    u32 argc = cnt - 1;
    if (replace) {
        ++argc;
        argv[4] = "REPLACE";
        lens[4] = sizeof("REPLACE") - 1;
    }

    if (isClusterMode()) {
        return launch(hashSlot(key1, keyLen1), argc, argv, lens);
    }
    return launch(argc, argv, lens);
}

bool CRedisRequest::scan(u32 offset, const c8* pattern, u32 patLen, u32 count) {
    const u32 max = 6;
    const c8* argv[max];
    u32 lens[max];

    argv[0] = "SCAN";
    lens[0] = sizeof("SCAN") - 1;

    c8 buf[16];
    snprintf(buf, sizeof(buf), "%u", offset);
    argv[1] = buf;
    lens[1] = (u32)strlen(buf);

    u32 cnt = 2;

    if (pattern && patLen > 0) {
        argv[2] = "MATCH";
        lens[2] = sizeof("MATCH") - 1;

        argv[3] = pattern;
        lens[3] = patLen;

        cnt += 2;
    }

    if (count > 0) {
        argv[cnt] = "COUNT";
        lens[cnt++] = sizeof("COUNT") - 1;

        c8 buf2[16];
        snprintf(buf2, sizeof(buf2), "%u", count);
        argv[cnt] = buf2;
        lens[cnt++] = (u32)strlen(buf2);
    }

    return launch(cnt, argv, lens);
}

bool CRedisRequest::migrate(const c8* ip, u16 port, const c8* key, u32 keyLen,
    u32 destDB, u32 timeout, c8 flag) {
    const u32 max = 7;
    const c8* argv[max];
    u32 lens[max];

    argv[0] = "MIGRATE";
    lens[0] = sizeof("MIGRATE") - 1;

    argv[1] = ip;
    lens[1] = (u32)strlen(ip);

    c8 buf[16];
    snprintf(buf, sizeof(buf), "%u", port);
    argv[2] = buf;
    lens[2] = (u32)strlen(buf);

    argv[3] = key;
    lens[3] = keyLen;

    c8 buf2[16];
    snprintf(buf2, sizeof(buf2), "%u", destDB);
    argv[4] = buf2;
    lens[4] = (u32)strlen(buf2);

    c8 buf3[16];
    snprintf(buf3, sizeof(buf3), "%u", timeout);
    argv[5] = buf3;
    lens[5] = (u32)strlen(buf3);

    u32 cnt = 6;
    if ('c' == flag) {
        argv[6] = "COPY";
        lens[6] = sizeof("COPY") - 1;
        ++cnt;
    } else if ('r' == flag) {
        argv[6] = "REPLACE";
        lens[6] = sizeof("REPLACE") - 1;
        ++cnt;
    }

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

} //namespace db {
} // namespace irr

