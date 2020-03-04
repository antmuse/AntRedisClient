#include "CRedisRequest.h"

namespace irr {
namespace db {

bool CRedisRequest::zadd(const c8* key, u32 keyLen, const c8** val, const u32* valLens, u32 count) {
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

    argv[0] = "ZADD";
    lens[0] = sizeof("ZADD") - 1;

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

bool CRedisRequest::zrem(const c8* key, u32 keyLen, const c8** val, const u32* valLens, u32 count) {
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

    argv[0] = "ZREM";
    lens[0] = sizeof("ZREM") - 1;

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

bool CRedisRequest::zscore(const c8* key, u32 keyLen, const c8* val, const u32 valLen) {
    if (nullptr == key || 0 == keyLen || nullptr == val || 0 == valLen) {
        return false;
    }
    const u32 cnt = 3;
    const c8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "ZSCORE";
    lens[0] = sizeof("ZSCORE") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    argv[2] = val;
    lens[2] = valLen;

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::zincrby(const c8* key, u32 keyLen, const c8* val, const u32 valLen, s32 value) {
    if (nullptr == key || 0 == keyLen || nullptr == val || 0 == valLen) {
        return false;
    }
    const u32 cnt = 4;
    const c8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "ZINCRBY";
    lens[0] = sizeof("ZINCRBY") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    c8 buf[16];
    snprintf(buf, sizeof(buf), "%d", value);
    argv[2] = buf;
    lens[2] = (u32)::strlen(buf);

    argv[3] = val;
    lens[3] = valLen;

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::zrank(const c8* key, u32 keyLen, const c8* val, const u32 valLen) {
    if (nullptr == key || 0 == keyLen || nullptr == val || 0 == valLen) {
        return false;
    }
    const u32 cnt = 3;
    const c8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "ZRANK";
    lens[0] = sizeof("ZRANK") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    argv[2] = val;
    lens[2] = valLen;

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::zrevrank(const c8* key, u32 keyLen, const c8* val, const u32 valLen) {
    if (nullptr == key || 0 == keyLen || nullptr == val || 0 == valLen) {
        return false;
    }
    const u32 cnt = 3;
    const c8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "ZREVRANK";
    lens[0] = sizeof("ZREVRANK") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    argv[2] = val;
    lens[2] = valLen;

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::zcard(const c8* key, u32 keyLen) {
    if (nullptr == key || 0 == keyLen) {
        return false;
    }
    const u32 cnt = 2;
    const c8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "ZCARD";
    lens[0] = sizeof("ZCARD") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::zcount(const c8* key, u32 keyLen, s32 min, s32 max) {
    if (nullptr == key || 0 == keyLen) {
        return false;
    }
    const u32 cnt = 4;
    const c8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "ZCOUNT";
    lens[0] = sizeof("ZCOUNT") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    c8 buf[16];
    snprintf(buf, sizeof(buf), "%d", min);
    argv[2] = buf;
    lens[2] = (u32)::strlen(buf);

    c8 buf2[16];
    snprintf(buf2, sizeof(buf2), "%d", max);
    argv[3] = buf2;
    lens[3] = (u32)::strlen(buf2);

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::zrange(const c8* key, u32 keyLen, s32 start, s32 stop, bool withScore) {
    if (nullptr == key || 0 == keyLen) {
        return false;
    }
    const u32 max = 5;
    const c8* argv[max];
    u32 lens[max];
    argv[0] = "ZRANGE";
    lens[0] = sizeof("ZRANGE") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    c8 buf[16];
    snprintf(buf, sizeof(buf), "%d", start);
    argv[2] = buf;
    lens[2] = (u32)::strlen(buf);

    c8 buf2[16];
    snprintf(buf2, sizeof(buf2), "%d", stop);
    argv[3] = buf2;
    lens[3] = (u32)::strlen(buf2);

    u32 cnt = 4;
    if (withScore) {
        argv[4] = key;
        lens[4] = keyLen;
        ++cnt;
    }

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::zremrangebyrank(const c8* key, u32 keyLen, s32 start, s32 stop) {
    if (nullptr == key || 0 == keyLen) {
        return false;
    }
    const u32 cnt = 4;
    const c8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "ZREMRANGEBYRANK";
    lens[0] = sizeof("ZREMRANGEBYRANK") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    c8 buf[16];
    snprintf(buf, sizeof(buf), "%d", start);
    argv[2] = buf;
    lens[2] = (u32)::strlen(buf);

    c8 buf2[16];
    snprintf(buf2, sizeof(buf2), "%d", stop);
    argv[3] = buf2;
    lens[3] = (u32)::strlen(buf2);


    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::zrevrange(const c8* key, u32 keyLen, s32 start, s32 stop, bool withScore) {
    if (nullptr == key || 0 == keyLen) {
        return false;
    }
    const u32 max = 5;
    const c8* argv[max];
    u32 lens[max];
    argv[0] = "ZREVRANGE";
    lens[0] = sizeof("ZREVRANGE") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    c8 buf[16];
    snprintf(buf, sizeof(buf), "%d", start);
    argv[2] = buf;
    lens[2] = (u32)::strlen(buf);

    c8 buf2[16];
    snprintf(buf2, sizeof(buf2), "%d", stop);
    argv[3] = buf2;
    lens[3] = (u32)::strlen(buf2);

    u32 cnt = 4;
    if (withScore) {
        argv[4] = key;
        lens[4] = keyLen;
        ++cnt;
    }

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::zrangebyscore(const c8* key, u32 keyLen, f32 iMin, f32 iMax, u32 flag, bool withScore) {
    if (nullptr == key || 0 == keyLen) {
        return false;
    }
    const u32 max = 5;
    const c8* argv[max];
    u32 lens[max];
    argv[0] = "ZRANGEBYSCORE";
    lens[0] = sizeof("ZRANGEBYSCORE") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    c8 buf[16];
    if (0 != (flag & 2U)) {
        snprintf(buf, sizeof(buf), "-inf");
    } else if (0 != (flag & 1U)) {
        snprintf(buf, sizeof(buf), "(%f", iMin);
    } else {
        snprintf(buf, sizeof(buf), "%f", iMin);
    }
    argv[2] = buf;
    lens[2] = (u32)::strlen(buf);

    c8 buf2[16];
    if (0 != (flag & 8U)) {
        snprintf(buf2, sizeof(buf2), "+inf");
    } else if (0 != (flag & 4U)) {
        snprintf(buf2, sizeof(buf2), "(%f", iMax);
    } else {
        snprintf(buf2, sizeof(buf2), "%f", iMax);
    }
    argv[3] = buf2;
    lens[3] = (u32)::strlen(buf2);

    u32 cnt = 4;
    if (withScore) {
        argv[4] = "WITHSCORES";
        lens[4] = sizeof("WITHSCORES") - 1;
        ++cnt;
    }

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::zrevrangebyscore(const c8* key, u32 keyLen, f32 iMin, f32 iMax, u32 flag, bool withScore) {
    if (nullptr == key || 0 == keyLen) {
        return false;
    }
    const u32 max = 5;
    const c8* argv[max];
    u32 lens[max];
    argv[0] = "ZREVRANGEBYSCORE";
    lens[0] = sizeof("ZREVRANGEBYSCORE") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    c8 buf[16];
    if (0 != (flag & 2U)) {
        snprintf(buf, sizeof(buf), "-inf");
    } else if (0 != (flag & 1U)) {
        snprintf(buf, sizeof(buf), "(%f", iMax);
    } else {
        snprintf(buf, sizeof(buf), "%f", iMax);
    }
    argv[2] = buf;
    lens[2] = (u32)::strlen(buf);

    c8 buf2[16];
    if (0 != (flag & 8U)) {
        snprintf(buf2, sizeof(buf2), "+inf");
    } else if (0 != (flag & 4U)) {
        snprintf(buf2, sizeof(buf2), "(%f", iMin);
    } else {
        snprintf(buf2, sizeof(buf2), "%f", iMin);
    }
    argv[3] = buf2;
    lens[3] = (u32)::strlen(buf2);

    u32 cnt = 4;
    if (withScore) {
        argv[4] = "WITHSCORES";
        lens[4] = sizeof("WITHSCORES") - 1;
        ++cnt;
    }

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::zremrangebyscore(const c8* key, u32 keyLen, f32 iMin, f32 iMax, u32 flag) {
    if (nullptr == key || 0 == keyLen) {
        return false;
    }
    const u32 cnt = 4;
    const c8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "ZRANGEBYSCORE";
    lens[0] = sizeof("ZRANGEBYSCORE") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    c8 buf[16];
    if (0 != (flag & 2U)) {
        snprintf(buf, sizeof(buf), "-inf");
    } else if (0 != (flag & 1U)) {
        snprintf(buf, sizeof(buf), "(%f", iMin);
    } else {
        snprintf(buf, sizeof(buf), "%f", iMin);
    }
    argv[2] = buf;
    lens[2] = (u32)::strlen(buf);

    c8 buf2[16];
    if (0 != (flag & 8U)) {
        snprintf(buf2, sizeof(buf2), "+inf");
    } else if (0 != (flag & 4U)) {
        snprintf(buf2, sizeof(buf2), "(%f", iMax);
    } else {
        snprintf(buf2, sizeof(buf2), "%f", iMax);
    }
    argv[3] = buf2;
    lens[3] = (u32)::strlen(buf2);

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::zrangebylex(const c8* key, u32 keyLen,
    const c8* min, u32 minLen, const c8* max, u32 maxLen) {
    if (nullptr == key || 0 == keyLen
        || nullptr == min || 0 == minLen
        || nullptr == max || 0 == maxLen) {
        return false;
    }
    const u32 cnt = 4;
    const c8* argv[cnt];
    u32 lens[cnt];

    argv[0] = "ZRANGEBYLEX";
    lens[0] = sizeof("ZRANGEBYLEX") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    argv[2] = min;
    lens[2] = minLen;

    argv[3] = max;
    lens[3] = maxLen;

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::zlexcount(const c8* key, u32 keyLen,
    const c8* min, u32 minLen, const c8* max, u32 maxLen) {
    if (nullptr == key || 0 == keyLen
        || nullptr == min || 0 == minLen
        || nullptr == max || 0 == maxLen) {
        return false;
    }
    const u32 cnt = 4;
    const c8* argv[cnt];
    u32 lens[cnt];

    argv[0] = "ZLEXCOUNT";
    lens[0] = sizeof("ZLEXCOUNT") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    argv[2] = min;
    lens[2] = minLen;

    argv[3] = max;
    lens[3] = maxLen;

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::zremrangebylex(const c8* key, u32 keyLen,
    const c8* min, u32 minLen, const c8* max, u32 maxLen) {
    if (nullptr == key || 0 == keyLen
        || nullptr == min || 0 == minLen
        || nullptr == max || 0 == maxLen) {
        return false;
    }
    const u32 cnt = 4;
    const c8* argv[cnt];
    u32 lens[cnt];

    argv[0] = "ZREMRANGEBYLEX";
    lens[0] = sizeof("ZREMRANGEBYLEX") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    argv[2] = min;
    lens[2] = minLen;

    argv[3] = max;
    lens[3] = maxLen;

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::zscan(const c8* key, u32 keyLen, u32 offset, const c8* pattern, u32 patLen, u32 count) {
    if (nullptr == key || 0 == keyLen) {
        return false;
    }
    const u32 max = 7;
    const c8* argv[max];
    u32 lens[max];

    argv[0] = "ZSCAN";
    lens[0] = sizeof("ZSCAN") - 1;

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

    if (count > 0) {
        argv[cnt] = "COUNT";
        lens[cnt++] = sizeof("COUNT") - 1;

        c8 buf2[16];
        snprintf(buf2, sizeof(buf2), "%u", count);
        argv[cnt] = buf2;
        lens[cnt++] = (u32)strlen(buf2);
    }

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}


bool CRedisRequest::zunionstore(const c8* destkey, u32 destkeyLen,
    const c8** keys, const u32* keyLens,
    const c8** weight, const u32* weightLens,
    u32 count, s32 aggregate) {
    if (nullptr == destkey || 0 == destkeyLen || 0 == count
        || nullptr == keys || nullptr == keyLens
        || nullptr == weight || nullptr == weightLens) {
        return false;
    }

    const u32 start = 2;
    const u32 maxcache = 128;
    c8* tmp_argv[maxcache];
    u32 tmp_size[maxcache];
    const u32 cnt = start + 2 * count + 1;
    c8** argv = cnt > maxcache ? new c8*[cnt] : tmp_argv;
    u32* lens = cnt > maxcache ? new u32[cnt] : tmp_size;

    argv[0] = "ZUNIONSTORE";
    lens[0] = sizeof("ZUNIONSTORE") - 1;

    c8 num[16];
    argv[1] = num;
    lens[1] = snprintf(num, sizeof(num), "%u", count);

    for (u32 i = 0; i < count; ++i) {
        argv[i + start] = const_cast<c8*>(keys[i]);
        lens[i + start] = keyLens[i];
    }
    for (u32 i = 0; i < count; ++i) {
        argv[i + start + count] = const_cast<c8*>(weight[i]);
        lens[i + start + count] = weightLens[i];
    }
    argv[start + 2 * count] = (0 == aggregate ? "SUM" : (aggregate > 0 ? "MAX" : "MIN"));
    lens[start + 2 * count] = 3;

    bool ret;
    if (isClusterMode()) {
        ret = launch(hashSlot(destkey, destkeyLen), cnt, const_cast<const c8**>(argv), lens);
    } else {
        ret = launch(cnt, const_cast<const c8**>(argv), lens);
    }
    if (cnt > maxcache) {
        delete[] argv;
        delete[] lens;
    }
    return ret;
}


bool CRedisRequest::zinterstore(const c8* destkey, u32 destkeyLen,
    const c8** keys, const u32* keyLens,
    const c8** weight, const u32* weightLens,
    u32 count, s32 aggregate) {
    if (nullptr == destkey || 0 == destkeyLen || 0 == count
        || nullptr == keys || nullptr == keyLens
        || nullptr == weight || nullptr == weightLens) {
        return false;
    }

    const u32 start = 2;
    const u32 maxcache = 128;
    c8* tmp_argv[maxcache];
    u32 tmp_size[maxcache];
    const u32 cnt = start + 2 * count + 1;
    c8** argv = cnt > maxcache ? new c8*[cnt] : tmp_argv;
    u32* lens = cnt > maxcache ? new u32[cnt] : tmp_size;

    argv[0] = "ZINTERSTORE";
    lens[0] = sizeof("ZINTERSTORE") - 1;

    c8 num[16];
    argv[1] = num;
    lens[1] = snprintf(num, sizeof(num), "%u", count);

    for (u32 i = 0; i < count; ++i) {
        argv[i + start] = const_cast<c8*>(keys[i]);
        lens[i + start] = keyLens[i];
    }
    for (u32 i = 0; i < count; ++i) {
        argv[i + start + count] = const_cast<c8*>(weight[i]);
        lens[i + start + count] = weightLens[i];
    }
    argv[start + 2 * count] = (0 == aggregate ? "SUM" : (aggregate > 0 ? "MAX" : "MIN"));
    lens[start + 2 * count] = 3;

    bool ret;
    if (isClusterMode()) {
        ret = launch(hashSlot(destkey, destkeyLen), cnt, const_cast<const c8**>(argv), lens);
    } else {
        ret = launch(cnt, const_cast<const c8**>(argv), lens);
    }
    if (cnt > maxcache) {
        delete[] argv;
        delete[] lens;
    }
    return ret;
}

} //namespace db {
} // namespace irr

