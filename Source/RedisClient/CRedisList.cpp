#include "CRedisRequest.h"

namespace irr {
namespace db {

bool CRedisRequest::llen(const c8* key, u32 keyLen) {
    if (nullptr == key || 0 == keyLen) {
        return false;
    }
    const u32 cnt = 2;
    const c8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "LLEN";
    lens[0] = sizeof("LLEN") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::lset(const c8* key, u32 keyLen, u32 pos, const c8* val, u32 valLen) {
    if (nullptr == key || 0 == keyLen || nullptr == val || 0 == valLen) {
        return false;
    }
    const u32 cnt = 4;
    const c8* argv[cnt];
    u32 lens[cnt];

    argv[0] = "LSET";
    lens[0] = sizeof("LSET") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    c8 buf[16];
    snprintf(buf, sizeof(buf), "%u", pos);
    argv[2] = buf;
    lens[2] = (u32)strlen(buf);

    argv[3] = val;
    lens[3] = valLen;

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::linsert(const c8* key, u32 keyLen, const c8* pivot, u32 pivotLen,
    const c8* val, u32 valLen, bool after) {
    if (nullptr == key || 0 == keyLen || nullptr == val || 0 == valLen || nullptr == pivot || 0 == pivotLen) {
        return false;
    }
    const u32 cnt = 5;
    const c8* argv[cnt];
    u32 lens[cnt];

    argv[0] = "LINSERT";
    lens[0] = sizeof("LINSERT") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    if (after) {
        argv[2] = "AFTER";
        lens[2] = sizeof("AFTER") - 1;
    } else {
        argv[2] = "BEFORE";
        lens[2] = sizeof("BEFORE") - 1;
    }

    argv[3] = pivot;
    lens[3] = pivotLen;

    argv[4] = val;
    lens[4] = valLen;

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::lindex(const c8* key, u32 keyLen, u32 pos) {
    if (nullptr == key || 0 == keyLen) {
        return false;
    }
    const u32 cnt = 3;
    const c8* argv[cnt];
    u32 lens[cnt];

    argv[0] = "LINDEX";
    lens[0] = sizeof("LINDEX") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    c8 buf[16];
    snprintf(buf, sizeof(buf), "%u", pos);
    argv[2] = buf;
    lens[2] = (u32)strlen(buf);

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::lrem(const c8* key, u32 keyLen, s32 pos, const c8* val, u32 valLen) {
    if (nullptr == key || 0 == keyLen || nullptr == val || 0 == valLen) {
        return false;
    }
    const u32 cnt = 4;
    const c8* argv[cnt];
    u32 lens[cnt];

    argv[0] = "LREM";
    lens[0] = sizeof("LREM") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    c8 buf[16];
    snprintf(buf, sizeof(buf), "%d", pos);
    argv[2] = buf;
    lens[2] = (u32)strlen(buf);

    argv[3] = val;
    lens[3] = valLen;

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::lpush(const c8* key, u32 keyLen, const c8* val, u32 valLen) {
    if (nullptr == key || 0 == keyLen || nullptr == val || 0 == valLen) {
        return false;
    }
    const u32 cnt = 3;
    const c8* argv[cnt];
    u32 lens[cnt];

    argv[0] = "LPUSH";
    lens[0] = sizeof("LPUSH") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    argv[2] = val;
    lens[2] = valLen;

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::rpush(const c8* key, u32 keyLen, const c8* val, u32 valLen) {
    if (nullptr == key || 0 == keyLen || nullptr == val || 0 == valLen) {
        return false;
    }
    const u32 cnt = 3;
    const c8* argv[cnt];
    u32 lens[cnt];

    argv[0] = "RPUSH";
    lens[0] = sizeof("RPUSH") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    argv[2] = val;
    lens[2] = valLen;

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::lpushx(const c8* key, u32 keyLen, const c8* val, u32 valLen) {
    if (nullptr == key || 0 == keyLen || nullptr == val || 0 == valLen) {
        return false;
    }
    const u32 cnt = 3;
    const c8* argv[cnt];
    u32 lens[cnt];

    argv[0] = "LPUSHX";
    lens[0] = sizeof("LPUSHX") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    argv[2] = val;
    lens[2] = valLen;

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::rpushx(const c8* key, u32 keyLen, const c8* val, u32 valLen) {
    if (nullptr == key || 0 == keyLen || nullptr == val || 0 == valLen) {
        return false;
    }
    const u32 cnt = 3;
    const c8* argv[cnt];
    u32 lens[cnt];

    argv[0] = "RPUSHX";
    lens[0] = sizeof("RPUSHX") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    argv[2] = val;
    lens[2] = valLen;

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::rpoplpush(const c8* key, u32 keyLen, const c8* val, u32 valLen) {
    if (nullptr == key || 0 == keyLen || nullptr == val || 0 == valLen) {
        return false;
    }
    const u32 cnt = 3;
    const c8* argv[cnt];
    u32 lens[cnt];

    argv[0] = "RPOPLPUSH";
    lens[0] = sizeof("RPOPLPUSH") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    argv[2] = val;
    lens[2] = valLen;

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::brpoplpush(const c8* key, u32 keyLen, const c8* val, u32 valLen) {
    if (nullptr == key || 0 == keyLen || nullptr == val || 0 == valLen) {
        return false;
    }
    const u32 cnt = 3;
    const c8* argv[cnt];
    u32 lens[cnt];

    argv[0] = "BRPOPLPUSH";
    lens[0] = sizeof("BRPOPLPUSH") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    argv[2] = val;
    lens[2] = valLen;

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::lrange(const c8* key, u32 keyLen, s32 start, s32 end) {
    if (nullptr == key || 0 == keyLen) {
        return false;
    }
    const u32 cnt = 4;
    const c8* argv[cnt];
    u32 lens[cnt];

    argv[0] = "LRANGE";
    lens[0] = sizeof("LRANGE") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    c8 buf[16];
    snprintf(buf, sizeof(buf), "%d", start);
    argv[2] = buf;
    lens[2] = (u32)strlen(buf);

    c8 buf2[16];
    snprintf(buf2, sizeof(buf2), "%d", end);
    argv[3] = buf2;
    lens[3] = (u32)strlen(buf2);

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::ltrim(const c8* key, u32 keyLen, s32 start, s32 end) {
    if (nullptr == key || 0 == keyLen) {
        return false;
    }
    const u32 cnt = 4;
    const c8* argv[cnt];
    u32 lens[cnt];

    argv[0] = "LTRIM";
    lens[0] = sizeof("LTRIM") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    c8 buf[16];
    snprintf(buf, sizeof(buf), "%d", start);
    argv[2] = buf;
    lens[2] = (u32)strlen(buf);

    c8 buf2[16];
    snprintf(buf2, sizeof(buf2), "%d", end);
    argv[3] = buf2;
    lens[3] = (u32)strlen(buf2);

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::rpop(const c8* key, u32 keyLen) {
    if (nullptr == key || 0 == keyLen) {
        return false;
    }
    const u32 cnt = 2;
    const c8* argv[cnt];
    u32 lens[cnt];

    argv[0] = "RPOP";
    lens[0] = sizeof("RPOP") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::lpop(const c8* key, u32 keyLen) {
    if (nullptr == key || 0 == keyLen) {
        return false;
    }
    const u32 cnt = 2;
    const c8* argv[cnt];
    u32 lens[cnt];

    argv[0] = "LPOP";
    lens[0] = sizeof("LPOP") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::brpop(const c8* key, u32 keyLen) {
    if (nullptr == key || 0 == keyLen) {
        return false;
    }
    const u32 cnt = 2;
    const c8* argv[cnt];
    u32 lens[cnt];

    argv[0] = "BRPOP";
    lens[0] = sizeof("BRPOP") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

bool CRedisRequest::blpop(const c8* key, u32 keyLen) {
    if (nullptr == key || 0 == keyLen) {
        return false;
    }
    const u32 cnt = 2;
    const c8* argv[cnt];
    u32 lens[cnt];

    argv[0] = "BLPOP";
    lens[0] = sizeof("BLPOP") - 1;

    argv[1] = key;
    lens[1] = keyLen;

    if (isClusterMode()) {
        return launch(hashSlot(key, keyLen), cnt, argv, lens);
    }
    return launch(cnt, argv, lens);
}

} //namespace db {
} // namespace irr

