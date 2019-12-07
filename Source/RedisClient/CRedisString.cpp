#include "CRedisRequest.h"

namespace irr {
namespace db {

bool CRedisRequest::set(const c8* key, const c8* value) {
    return set(key, static_cast<u32>(::strlen(key)),
        value, static_cast<u32>(::strlen(value)));
}

bool CRedisRequest::set(const c8* key, u32 keyLen,
    const c8* value, u32 valLen) {
    const c8* argv[3];
    u32 lens[3];
    argv[0] = "SET";
    lens[0] = 3;

    argv[1] = key;
    lens[1] = keyLen;

    argv[2] = value;
    lens[2] = valLen;

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), 3, argv, lens);
    }
    return launch(3, argv, lens);
}

bool CRedisRequest::getset(const c8* key, u32 keyLen,
    const c8* value, u32 valLen) {
    const u32 cnt = 3;
    const c8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "GETSET";
    lens[0] = sizeof("GETSET") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    argv[2] = value;
    lens[2] = valLen;

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::setnx(const c8* key, u32 keyLen,
    const c8* value, u32 valLen) {
    const c8* argv[3];
    u32 lens[3];
    argv[0] = "SETNX";
    lens[0] = sizeof("SETNX") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    argv[2] = value;
    lens[2] = valLen;

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), 3, argv, lens);
    }
    return launch(3, argv, lens);
}

bool CRedisRequest::get(const c8* key) {
    return get(key, static_cast<u32>(::strlen(key)));
}

bool CRedisRequest::get(const c8* key, u32 len) {
    const u32 cnt = 2;
    const c8* argv[cnt];
    u32 lens[cnt];

    argv[0] = "GET";
    lens[0] = sizeof("GET") - 1;

    argv[1] = key;
    lens[1] = len;

    if (isClusterMode()) {
        return launch(hashSlot(key), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::incr(const c8* key, u32 len) {
    const u32 cnt = 2;
    const c8* argv[cnt];
    u32 lens[cnt];

    argv[0] = "INCR";
    lens[0] = sizeof("INCR") - 1;

    argv[1] = key;
    lens[1] = len;

    if (isClusterMode()) {
        return launch(hashSlot(key), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::incrby(const c8* key, u32 len, s32 addon) {
    const u32 cnt = 3;
    const c8* argv[cnt];
    u32 lens[cnt];

    argv[0] = "INCRBY";
    lens[0] = sizeof("INCRBY") - 1;

    argv[1] = key;
    lens[1] = len;

    c8 buf[16];
    snprintf(buf, sizeof(buf), "%d", addon);
    argv[2] = buf;
    lens[2] = (u32)::strlen(buf);

    if (isClusterMode()) {
        return launch(hashSlot(key), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::decr(const c8* key, u32 len) {
    const u32 cnt = 2;
    const c8* argv[cnt];
    u32 lens[cnt];

    argv[0] = "DECR";
    lens[0] = sizeof("DECR") - 1;

    argv[1] = key;
    lens[1] = len;

    if (isClusterMode()) {
        return launch(hashSlot(key), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::decrby(const c8* key, u32 len, s32 addon) {
    const u32 cnt = 3;
    const c8* argv[cnt];
    u32 lens[cnt];

    argv[0] = "DECRBY";
    lens[0] = sizeof("DECRBY") - 1;

    argv[1] = key;
    lens[1] = len;

    c8 buf[16];
    snprintf(buf, sizeof(buf), "%d", addon);
    argv[2] = buf;
    lens[2] = (u32)::strlen(buf);

    if (isClusterMode()) {
        return launch(hashSlot(key), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::incrbyfloat(const c8* key, u32 len, f64 addon) {
    const u32 cnt = 3;
    const c8* argv[cnt];
    u32 lens[cnt];

    argv[0] = "INCRBYFLOAT";
    lens[0] = sizeof("INCRBYFLOAT") - 1;

    argv[1] = key;
    lens[1] = len;

    c8 buf[64];
    snprintf(buf, sizeof(buf), "%lf", addon);
    argv[2] = buf;
    lens[2] = (u32)::strlen(buf);

    if (isClusterMode()) {
        return launch(hashSlot(key), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::stringlen(const c8* key, u32 len) {
    const u32 cnt = 2;
    const c8* argv[cnt];
    u32 lens[cnt];

    argv[0] = "STRLEN";
    lens[0] = sizeof("STRLEN") - 1;

    argv[1] = key;
    lens[1] = len;

    if (isClusterMode()) {
        return launch(hashSlot(key), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::setex(const c8* key, u32 keyLen, const c8* value, u32 valLen, u32 timeout) {
    const u32 cnt = 4;
    const c8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "SETEX";
    lens[0] = sizeof("SETEX") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    c8 buf[16];
    snprintf(buf, sizeof(buf), "%u", timeout);
    argv[2] = buf;
    lens[2] = (u32)::strlen(buf);

    argv[3] = value;
    lens[3] = valLen;

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::psetex(const c8* key, u32 keyLen, const c8* value, u32 valLen, u32 timeout) {
    const u32 cnt = 4;
    const c8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "PSETEX";
    lens[0] = sizeof("PSETEX") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    c8 buf[16];
    snprintf(buf, sizeof(buf), "%u", timeout);
    argv[2] = buf;
    lens[2] = (u32)::strlen(buf);

    argv[3] = value;
    lens[3] = valLen;

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::append(const c8* key, u32 keyLen,
    const c8* value, u32 valLen) {
    const u32 cnt = 3;
    const c8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "APPEND";
    lens[0] = sizeof("APPEND") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    argv[2] = value;
    lens[2] = valLen;

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}


bool CRedisRequest::setrange(const c8* key, u32 keyLen, const c8* value, u32 valLen, u32 offset) {
    const u32 cnt = 4;
    const c8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "SETRANGE";
    lens[0] = sizeof("SETRANGE") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    c8 buf[16];
    snprintf(buf, sizeof(buf), "%u", offset);
    argv[2] = buf;
    lens[2] = (u32)::strlen(buf);

    argv[3] = value;
    lens[3] = valLen;

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}


bool CRedisRequest::getrange(const c8* key, u32 keyLen, s32 start, s32 end) {
    const u32 cnt = 4;
    const c8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "GETRANGE";
    lens[0] = sizeof("GETRANGE") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    c8 buf[16];
    snprintf(buf, sizeof(buf), "%d", start);
    argv[2] = buf;
    lens[2] = (u32)::strlen(buf);

    c8 buf2[16];
    snprintf(buf2, sizeof(buf2), "%d", end);
    argv[3] = buf2;
    lens[3] = (u32)::strlen(buf2);

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::mset(const c8** key, const u32* keyLen, u32 count) {
    if (count > 0x7FFFFFFF || isClusterMode()) {
        return false;
    }
    const u32 cnt = 1 + count;
    c8** argv = new c8*[cnt];
    u32* lens = new u32[cnt];

    argv[0] = "MSET";
    lens[0] = sizeof("MSET") - 1;

    for (u32 i = 1; i <= count; ++i) {
        argv[i] = const_cast<c8*>(key[i]);
        lens[i] = keyLen[i];
    }

    bool ret = launch(cnt, const_cast<const c8**>(argv), lens);
    delete[] argv;
    delete[] lens;
    return ret;
}

bool CRedisRequest::mget(const c8** key, const u32* keyLen, u32 count) {
    if (count > 0x7FFFFFFF || isClusterMode()) {
        return false;
    }

    const u32 cnt = 1 + count;
    c8** argv = new c8*[cnt];
    u32* lens = new u32[cnt];

    argv[0] = "MGET";
    lens[0] = sizeof("MGET") - 1;

    for (u32 i = 1; i <= count; ++i) {
        argv[i] = const_cast<c8*>(key[i]);
        lens[i] = keyLen[i];
    }

    bool ret = launch(cnt, const_cast<const c8**>(argv), lens);
    delete[] argv;
    delete[] lens;
    return ret;
}

bool CRedisRequest::msetnx(const c8** key, const u32* keyLen, u32 count) {
    if (count > 0x7FFFFFFF || isClusterMode()) {
        return false;
    }

    const u32 cnt = 1 + count;
    c8** argv = new c8*[cnt];
    u32* lens = new u32[cnt];

    argv[0] = "MSETNX";
    lens[0] = sizeof("MSETNX") - 1;

    for (u32 i = 1; i <= count; ++i) {
        argv[i] = const_cast<c8*>(key[i]);
        lens[i] = keyLen[i];
    }

    bool ret = launch(cnt, const_cast<const c8**>(argv), lens);
    delete[] argv;
    delete[] lens;
    return ret;
}

} //namespace db {
} // namespace irr

