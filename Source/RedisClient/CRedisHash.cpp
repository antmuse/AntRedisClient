#include "CRedisRequest.h"

namespace app {
namespace db {

bool CRedisRequest::hset(const s8* key, u32 keyLen,
    const s8* name, u32 nameLen, const s8* value, u32 valLen) {
    if (nullptr == key || 0 == keyLen || nullptr == name || 0 == nameLen
        || nullptr == value || 0 == valLen) {
        return false;
    }
    const u32 cnt = 4;
    const s8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "HSET";
    lens[0] = sizeof("HSET") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    argv[2] = name;
    lens[2] = nameLen;

    argv[3] = value;
    lens[3] = valLen;

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}


bool CRedisRequest::hsetnx(const s8* key, u32 keyLen,
    const s8* name, u32 nameLen, const s8* value, u32 valLen) {
    if (nullptr == key || 0 == keyLen || nullptr == name || 0 == nameLen
        || nullptr == value || 0 == valLen) {
        return false;
    }
    const u32 cnt = 4;
    const s8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "HSETNX";
    lens[0] = sizeof("HSETNX") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    argv[2] = name;
    lens[2] = nameLen;

    argv[3] = value;
    lens[3] = valLen;

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}


bool CRedisRequest::hget(const s8* key, u32 keyLen, const s8* name, u32 nameLen) {
    if (nullptr == key || 0 == keyLen || nullptr == name || 0 == nameLen) {
        return false;
    }
    const u32 cnt = 3;
    const s8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "HGET";
    lens[0] = sizeof("HGET") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    argv[2] = name;
    lens[2] = nameLen;

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::hgetall(const s8* key, u32 keyLen) {
    if (nullptr == key || 0 == keyLen) {
        return false;
    }
    const u32 cnt = 2;
    const s8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "HGETALL";
    lens[0] = sizeof("HGETALL") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::hexists(const s8* key, u32 keyLen, const s8* name, u32 nameLen) {
    if (nullptr == key || 0 == keyLen || nullptr == name || 0 == nameLen) {
        return false;
    }
    const u32 cnt = 3;
    const s8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "HEXISTS";
    lens[0] = sizeof("HEXISTS") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    argv[2] = name;
    lens[2] = nameLen;

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::hdel(const s8* key, u32 keyLen, const s8* name, u32 nameLen) {
    if (nullptr == key || 0 == keyLen || nullptr == name || 0 == nameLen) {
        return false;
    }
    const u32 cnt = 3;
    const s8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "HDEL";
    lens[0] = sizeof("HDEL") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    argv[2] = name;
    lens[2] = nameLen;

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::hlen(const s8* key, u32 keyLen) {
    if (nullptr == key || 0 == keyLen) {
        return false;
    }
    const u32 cnt = 2;
    const s8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "HLEN";
    lens[0] = sizeof("HLEN") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::hkeys(const s8* key, u32 keyLen) {
    if (nullptr == key || 0 == keyLen) {
        return false;
    }
    const u32 cnt = 2;
    const s8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "HKEYS";
    lens[0] = sizeof("HKEYS") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::hvals(const s8* key, u32 keyLen) {
    if (nullptr == key || 0 == keyLen) {
        return false;
    }
    const u32 cnt = 2;
    const s8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "HVALS";
    lens[0] = sizeof("HVALS") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::hstrlen(const s8* key, u32 keyLen, const s8* name, u32 nameLen) {
    if (nullptr == key || 0 == keyLen || nullptr == name || 0 == nameLen) {
        return false;
    }
    const u32 cnt = 3;
    const s8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "HSTRLEN";
    lens[0] = sizeof("HSTRLEN") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    argv[2] = name;
    lens[2] = nameLen;

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::hincrby(const s8* key, u32 keyLen, const s8* name, u32 nameLen, s32 val) {
    if (nullptr == key || 0 == keyLen || nullptr == name || 0 == nameLen) {
        return false;
    }
    const u32 cnt = 4;
    const s8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "HINCRBY";
    lens[0] = sizeof("HINCRBY") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    argv[2] = name;
    lens[2] = nameLen;

    s8 buf[16];
    snprintf(buf, sizeof(buf), "%d", val);
    argv[3] = buf;
    lens[3] = (u32)strlen(buf);

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::hincrbyfloat(const s8* key, u32 keyLen, const s8* name, u32 nameLen, f32 val) {
    if (nullptr == key || 0 == keyLen || nullptr == name || 0 == nameLen) {
        return false;
    }
    const u32 cnt = 4;
    const s8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "HINCRBYFLOAT";
    lens[0] = sizeof("HINCRBYFLOAT") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    argv[2] = name;
    lens[2] = nameLen;

    s8 buf[16];
    snprintf(buf, sizeof(buf), "%f", val);
    argv[3] = buf;
    lens[3] = (u32)strlen(buf);

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::hscan(const s8* key, u32 keyLen, u32 offset, const s8* pattern, u32 patLen, u32 count) {
    if (nullptr == key || 0 == keyLen) {
        return false;
    }
    const u32 max = 7;
    const s8* argv[max];
    u32 lens[max];

    argv[0] = "HSCAN";
    lens[0] = sizeof("HSCAN") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    s8 buf[16];
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

    if (count > 0) {
        argv[cnt] = "COUNT";
        lens[cnt++] = sizeof("COUNT") - 1;

        s8 buf2[16];
        snprintf(buf2, sizeof(buf2), "%u", count);
        argv[cnt] = buf2;
        lens[cnt++] = (u32)strlen(buf2);
    }

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::hmset(const s8* key, u32 keyLen, const s8** pairs, const u32* pairLens, u32 count) {
    if (nullptr == key || 0 == keyLen || nullptr == pairs || nullptr == pairLens || 0 == count) {
        return false;
    }
    const u32 start = 2;
    const u32 maxcache = 128;
    s8* tmp_argv[maxcache + start];
    u32 tmp_size[maxcache + start];
    const u32 cnt = start + count;
    s8** argv = count > maxcache ? new s8*[cnt] : tmp_argv;
    u32* lens = count > maxcache ? new u32[cnt] : tmp_size;

    argv[0] = "HMSET";
    lens[0] = sizeof("HMSET") - 1;

    argv[1] = const_cast<s8*>(key);
    lens[1] = keyLen;

    for (u32 i = 0; i < count; ++i) {
        argv[i + start] = const_cast<s8*>(pairs[i]);
        lens[i + start] = pairLens[i];
    }

    bool ret;
    if (isClusterMode()) {
        ret = launch(hashSlot(key, keyLen), cnt, const_cast<const s8**>(argv), lens);
    } else {
        ret = launch(cnt, const_cast<const s8**>(argv), lens);
    }
    if (count > maxcache) {
        delete[] argv;
        delete[] lens;
    }
    return ret;
}

bool CRedisRequest::hmget(const s8* key, u32 keyLen, const s8** name, const u32* nameLen, u32 count) {
    if (nullptr == key || 0 == keyLen || nullptr == name || nullptr == nameLen || 0 == count) {
        return false;
    }
    const u32 start = 2;
    const u32 maxcache = 128;
    s8* tmp_argv[maxcache + start];
    u32 tmp_size[maxcache + start];
    const u32 cnt = start + count;
    s8** argv = count > maxcache ? new s8*[cnt] : tmp_argv;
    u32* lens = count > maxcache ? new u32[cnt] : tmp_size;

    argv[0] = "HMGET";
    lens[0] = sizeof("HMGET") - 1;

    argv[1] = const_cast<s8*>(key);
    lens[1] = keyLen;

    for (u32 i = 0; i < count; ++i) {
        argv[i + start] = const_cast<s8*>(name[i]);
        lens[i + start] = nameLen[i];
    }

    bool ret;
    if (isClusterMode()) {
        ret = launch(hashSlot(key, keyLen), cnt, const_cast<const s8**>(argv), lens);
    } else {
        ret = launch(cnt, const_cast<const s8**>(argv), lens);
    }
    if (count > maxcache) {
        delete[] argv;
        delete[] lens;
    }
    return ret;
}

} //namespace db {
} // namespace app

