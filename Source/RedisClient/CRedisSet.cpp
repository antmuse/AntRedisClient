#include "CRedisRequest.h"

namespace irr {
namespace db {

bool CRedisRequest::sdiff(const c8** keys, const u32* keyLens, u32 count) {
    if (nullptr == keys || 0 == keyLens || count < 2) {
        return false;
    }
    const u32 start = 1;
    const u32 maxcache = 128;
    c8* tmp_argv[maxcache + start];
    u32 tmp_size[maxcache + start];
    const u32 cnt = start + count;
    c8** argv = count > maxcache ? new c8*[cnt] : tmp_argv;
    u32* lens = count > maxcache ? new u32[cnt] : tmp_size;

    argv[0] = "SDIFF";
    lens[0] = sizeof("SDIFF") - 1;

    for (u32 i = 0; i < count; ++i) {
        argv[i + start] = const_cast<c8*>(keys[i]);
        lens[i + start] = keyLens[i];
    }

    bool ret = launch(cnt, const_cast<const c8**>(argv), lens);
    if (count > maxcache) {
        delete[] argv;
        delete[] lens;
    }
    return ret;
}

bool CRedisRequest::sdiffstore(const c8* key, u32 keyLen, const c8** keys, const u32* keyLens, u32 count) {
    if (nullptr == key || 0 == keyLen || nullptr == keys || 0 == keyLens || count < 2) {
        return false;
    }
    const u32 start = 2;
    const u32 maxcache = 128;
    c8* tmp_argv[maxcache + start];
    u32 tmp_size[maxcache + start];
    const u32 cnt = start + count;
    c8** argv = count > maxcache ? new c8*[cnt] : tmp_argv;
    u32* lens = count > maxcache ? new u32[cnt] : tmp_size;

    argv[0] = "SDIFFSTORE";
    lens[0] = sizeof("SDIFFSTORE") - 1;

    argv[1] = const_cast<c8*>(key);
    lens[1] = keyLen;

    for (u32 i = 0; i < count; ++i) {
        argv[i + start] = const_cast<c8*>(keys[i]);
        lens[i + start] = keyLens[i];
    }

    bool ret = launch(cnt, const_cast<const c8**>(argv), lens);
    if (count > maxcache) {
        delete[] argv;
        delete[] lens;
    }
    return ret;
}

bool CRedisRequest::sinterstore(const c8* key, u32 keyLen, const c8** keys, const u32* keyLens, u32 count) {
    if (nullptr == key || 0 == keyLen || nullptr == keys || 0 == keyLens || count < 2) {
        return false;
    }
    const u32 start = 2;
    const u32 maxcache = 128;
    c8* tmp_argv[maxcache + start];
    u32 tmp_size[maxcache + start];
    const u32 cnt = start + count;
    c8** argv = count > maxcache ? new c8*[cnt] : tmp_argv;
    u32* lens = count > maxcache ? new u32[cnt] : tmp_size;

    argv[0] = "SINTERSTORE";
    lens[0] = sizeof("SINTERSTORE") - 1;

    argv[1] = const_cast<c8*>(key);
    lens[1] = keyLen;

    for (u32 i = 0; i < count; ++i) {
        argv[i + start] = const_cast<c8*>(keys[i]);
        lens[i + start] = keyLens[i];
    }

    bool ret = launch(cnt, const_cast<const c8**>(argv), lens);
    if (count > maxcache) {
        delete[] argv;
        delete[] lens;
    }
    return ret;
}

bool CRedisRequest::sinter(const c8** keys, const u32* keyLens, u32 count) {
    if (nullptr == keys || 0 == keyLens || count < 2) {
        return false;
    }
    const u32 start = 1;
    const u32 maxcache = 128;
    c8* tmp_argv[maxcache + start];
    u32 tmp_size[maxcache + start];
    const u32 cnt = start + count;
    c8** argv = count > maxcache ? new c8*[cnt] : tmp_argv;
    u32* lens = count > maxcache ? new u32[cnt] : tmp_size;

    argv[0] = "SINTER";
    lens[0] = sizeof("SINTER") - 1;

    for (u32 i = 0; i < count; ++i) {
        argv[i + start] = const_cast<c8*>(keys[i]);
        lens[i + start] = keyLens[i];
    }

    bool ret = launch(cnt, const_cast<const c8**>(argv), lens);
    if (count > maxcache) {
        delete[] argv;
        delete[] lens;
    }
    return ret;
}

bool CRedisRequest::sunion(const c8** keys, const u32* keyLens, u32 count) {
    if (nullptr == keys || 0 == keyLens || count < 2) {
        return false;
    }
    const u32 start = 1;
    const u32 maxcache = 128;
    c8* tmp_argv[maxcache + start];
    u32 tmp_size[maxcache + start];
    const u32 cnt = start + count;
    c8** argv = count > maxcache ? new c8*[cnt] : tmp_argv;
    u32* lens = count > maxcache ? new u32[cnt] : tmp_size;

    argv[0] = "SUNION";
    lens[0] = sizeof("SUNION") - 1;

    for (u32 i = 0; i < count; ++i) {
        argv[i + start] = const_cast<c8*>(keys[i]);
        lens[i + start] = keyLens[i];
    }

    bool ret = launch(cnt, const_cast<const c8**>(argv), lens);
    if (count > maxcache) {
        delete[] argv;
        delete[] lens;
    }
    return ret;
}

bool CRedisRequest::sunionstore(const c8* key, u32 keyLen, const c8** keys, const u32* keyLens, u32 count) {
    if (nullptr == key || 0 == keyLen || nullptr == keys || 0 == keyLens || count < 2) {
        return false;
    }
    const u32 start = 2;
    const u32 maxcache = 128;
    c8* tmp_argv[maxcache + start];
    u32 tmp_size[maxcache + start];
    const u32 cnt = start + count;
    c8** argv = count > maxcache ? new c8*[cnt] : tmp_argv;
    u32* lens = count > maxcache ? new u32[cnt] : tmp_size;

    argv[0] = "SUNIONSTORE";
    lens[0] = sizeof("SUNIONSTORE") - 1;

    argv[1] = const_cast<c8*>(key);
    lens[1] = keyLen;

    for (u32 i = 0; i < count; ++i) {
        argv[i + start] = const_cast<c8*>(keys[i]);
        lens[i + start] = keyLens[i];
    }

    bool ret = launch(cnt, const_cast<const c8**>(argv), lens);
    if (count > maxcache) {
        delete[] argv;
        delete[] lens;
    }
    return ret;
}

bool CRedisRequest::sadd(const c8* key, u32 keyLen, const c8* val, const u32 valLens) {
    if (nullptr == key || 0 == keyLen || nullptr == val || 0 == valLens) {
        return false;
    }
    return sadd(key, keyLen, &val, &valLens, 1);
}

bool CRedisRequest::sadd(const c8* key, u32 keyLen, const c8** val, const u32* valLens, u32 count) {
    if (nullptr == key || 0 == keyLen || nullptr == val || 0 == valLens || 0 == count) {
        return false;
    }
    const u32 start = 2;
    const u32 maxcache = 128;
    c8* tmp_argv[maxcache + start];
    u32 tmp_size[maxcache + start];
    const u32 cnt = start + count;
    c8** argv = count > maxcache ? new c8*[cnt] : tmp_argv;
    u32* lens = count > maxcache ? new u32[cnt] : tmp_size;

    argv[0] = "SADD";
    lens[0] = sizeof("SADD") - 1;

    argv[1] = const_cast<c8*>(key);
    lens[1] = keyLen;

    for (u32 i = 0; i < count; ++i) {
        argv[i + start] = const_cast<c8*>(val[i]);
        lens[i + start] = valLens[i];
    }

    bool ret;
    if (isClusterMode()) {
        ret = launch(hashSlot(key, keyLen), cnt, const_cast<const c8**>(argv), lens);
    } else {
        ret = launch(cnt, const_cast<const c8**>(argv), lens);
    }
    if (count > maxcache) {
        delete[] argv;
        delete[] lens;
    }
    return ret;
}

bool CRedisRequest::srem(const c8* key, u32 keyLen, const c8* val, const u32 valLens) {
    if (nullptr == key || 0 == keyLen || nullptr == val || 0 == valLens) {
        return false;
    }
    return srem(key, keyLen, &val, &valLens, 1);
}

bool CRedisRequest::srem(const c8* key, u32 keyLen, const c8** val, const u32* valLens, u32 count) {
    if (nullptr == key || 0 == keyLen || nullptr == val || 0 == valLens || 0 == count) {
        return false;
    }
    const u32 start = 2;
    const u32 maxcache = 128;
    c8* tmp_argv[maxcache + start];
    u32 tmp_size[maxcache + start];
    const u32 cnt = start + count;
    c8** argv = count > maxcache ? new c8*[cnt] : tmp_argv;
    u32* lens = count > maxcache ? new u32[cnt] : tmp_size;

    argv[0] = "SREM";
    lens[0] = sizeof("SREM") - 1;

    argv[1] = const_cast<c8*>(key);
    lens[1] = keyLen;

    for (u32 i = 0; i < count; ++i) {
        argv[i + start] = const_cast<c8*>(val[i]);
        lens[i + start] = valLens[i];
    }

    bool ret;
    if (isClusterMode()) {
        ret = launch(hashSlot(key, keyLen), cnt, const_cast<const c8**>(argv), lens);
    } else {
        ret = launch(cnt, const_cast<const c8**>(argv), lens);
    }
    if (count > maxcache) {
        delete[] argv;
        delete[] lens;
    }
    return ret;
}

bool CRedisRequest::sismember(const c8* key, u32 keyLen, const c8* val, u32 valLen) {
    if (nullptr == key || 0 == keyLen || nullptr == val || 0 == valLen) {
        return false;
    }
    const u32 cnt = 3;
    const c8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "SISMEMBER";
    lens[0] = sizeof("SISMEMBER") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    argv[2] = val;
    lens[2] = valLen;

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::spop(const c8* key, u32 keyLen) {
    if (nullptr == key || 0 == keyLen) {
        return false;
    }
    const u32 cnt = 2;
    const c8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "SPOP";
    lens[0] = sizeof("SPOP") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::scard(const c8* key, u32 keyLen) {
    if (nullptr == key || 0 == keyLen) {
        return false;
    }
    const u32 cnt = 2;
    const c8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "SCARD";
    lens[0] = sizeof("SCARD") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::smembers(const c8* key, u32 keyLen) {
    if (nullptr == key || 0 == keyLen) {
        return false;
    }
    const u32 cnt = 2;
    const c8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "SMEMBERS";
    lens[0] = sizeof("SMEMBERS") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::srandmember(const c8* key, u32 keyLen, u32 count) {
    if (nullptr == key || 0 == keyLen) {
        return false;
    }
    const u32 max = 3;
    const c8* argv[max];
    u32 lens[max];
    argv[0] = "SRANDMEMBER";
    lens[0] = sizeof("SRANDMEMBER") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    u32 cnt = 2;
    c8 buf[16];
    if (count > 0) {
        snprintf(buf, sizeof(buf), "%u", count);
        argv[2] = buf;
        lens[2] = (u32)::strlen(buf);
        ++cnt;
    }
    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::smove(const c8* key1, u32 keyLen1,
    const c8* key2, u32 keyLen2, const c8* val, const u32 valLen) {
    if (!key1 || 0 == keyLen1 || !key2 || 0 == keyLen2 || !val || 0 == valLen) {
        return false;
    }
    const u32 cnt = 4;
    const c8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "SMOVE";
    lens[0] = sizeof("SMOVE") - 1;

    argv[1] = key1;
    lens[1] = keyLen1;

    argv[2] = key2;
    lens[2] = keyLen2;

    argv[3] = val;
    lens[3] = valLen;

    if (isClusterMode()) {
        return launch(hashSlot(key1, keyLen1), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::sscan(const c8* key, u32 keyLen, u32 offset, const c8* pattern, u32 patLen, u32 count) {
    if (nullptr == key || 0 == keyLen) {
        return false;
    }
    const u32 max = 7;
    const c8* argv[max];
    u32 lens[max];

    argv[0] = "SSCAN";
    lens[0] = sizeof("SSCAN") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    c8 buf[16];
    snprintf(buf, sizeof(buf), "%u", offset);
    argv[2] = buf;
    lens[2] = (u32)strlen(buf);

    u32 cnt = 3;

    if (pattern && patLen > 0) {
        argv[2] = "MATCH";
        lens[2] = sizeof("MATCH") - 1;

        argv[3] = pattern;
        lens[3] = patLen;

        cnt += 2;
    }

    c8 buf2[16];
    if (count > 0) {
        argv[cnt] = "COUNT";
        lens[cnt++] = sizeof("COUNT") - 1;

        snprintf(buf2, sizeof(buf2), "%u", count);
        argv[cnt] = buf2;
        lens[cnt++] = (u32)strlen(buf2);
    }

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

} //namespace db {
} // namespace irr

