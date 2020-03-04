#include "CRedisRequest.h"

namespace irr {
namespace db {

bool CRedisRequest::setbit(const c8* key, u32 keyLen, u32 offset, bool val) {
    if (nullptr == key || 0 == keyLen) {
        return false;
    }
    const u32 cnt = 4;
    const c8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "SETBIT";
    lens[0] = sizeof("SETBIT") - 1;
    argv[1] = key;
    lens[1] = keyLen;
    c8 offsetstr[16];
    argv[2] = offsetstr;
    lens[2] = snprintf(offsetstr, sizeof(offsetstr), "%u", offset);
    argv[3] = val ? "1" : "0";
    lens[3] = 1;

    bool ret;
    if (isClusterMode()) {
        ret = launch(hashSlot(key, keyLen), cnt, const_cast<const c8**>(argv), lens);
    } else {
        ret = launch(cnt, const_cast<const c8**>(argv), lens);
    }
    return ret;
}

bool CRedisRequest::getbit(const c8* key, u32 keyLen, u32 offset) {
    if (nullptr == key || 0 == keyLen) {
        return false;
    }
    const u32 cnt = 3;
    const c8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "GETBIT";
    lens[0] = sizeof("GETBIT") - 1;
    argv[1] = key;
    lens[1] = keyLen;
    c8 offsetstr[16];
    argv[2] = offsetstr;
    lens[2] = snprintf(offsetstr, sizeof(offsetstr), "%u", offset);

    bool ret;
    if (isClusterMode()) {
        ret = launch(hashSlot(key, keyLen), cnt, const_cast<const c8**>(argv), lens);
    } else {
        ret = launch(cnt, const_cast<const c8**>(argv), lens);
    }
    return ret;
}


bool CRedisRequest::bitcount(const c8* key, u32 keyLen, u32 min, u32 max) {
    if (nullptr == key || 0 == keyLen) {
        return false;
    }
    const u32 cnt = 4;
    const c8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "BITCOUNT";
    lens[0] = sizeof("BITCOUNT") - 1;
    argv[1] = key;
    lens[1] = keyLen;
    c8 minstr[16];
    c8 maxstr[16];
    argv[2] = minstr;
    lens[2] = snprintf(minstr, sizeof(minstr), "%u", min);
    argv[3] = maxstr;
    lens[3] = snprintf(maxstr, sizeof(maxstr), "%u", max);

    bool ret;
    if (isClusterMode()) {
        ret = launch(hashSlot(key, keyLen), cnt, const_cast<const c8**>(argv), lens);
    } else {
        ret = launch(cnt, const_cast<const c8**>(argv), lens);
    }
    return ret;
}


bool CRedisRequest::bitpos(const c8* key, u32 keyLen, bool val, u32 min, u32 max) {
    if (nullptr == key || 0 == keyLen) {
        return false;
    }
    const u32 cnt = 5;
    const c8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "BITPOS";
    lens[0] = sizeof("BITPOS") - 1;
    argv[1] = key;
    lens[1] = keyLen;
    argv[2] = val ? "1" : "0";
    lens[2] = 1;
    c8 minstr[16];
    c8 maxstr[16];
    argv[3] = minstr;
    lens[3] = snprintf(minstr, sizeof(minstr), "%u", min);
    argv[4] = maxstr;
    lens[4] = snprintf(maxstr, sizeof(maxstr), "%u", max);

    bool ret;
    if (isClusterMode()) {
        ret = launch(hashSlot(key, keyLen), cnt, const_cast<const c8**>(argv), lens);
    } else {
        ret = launch(cnt, const_cast<const c8**>(argv), lens);
    }
    return ret;
}


bool CRedisRequest::bitop(const c8* key, u32 keyLen, u32 flag,
    const c8** val, const u32* valLens, u32 count) {
    if (nullptr == key || 0 == keyLen || nullptr == val || 0 == valLens
        || 0 == count) {
        return false;
    }
    const u32 start = 3;
    const u32 maxcache = 128;
    c8* tmp_argv[maxcache + start];
    u32 tmp_size[maxcache + start];
    const u32 cnt = start + count;
    c8** argv = count > maxcache ? new c8*[cnt] : tmp_argv;
    u32* lens = count > maxcache ? new u32[cnt] : tmp_size;

    argv[0] = "BITOP";
    lens[0] = sizeof("BITOP") - 1;
    switch (flag) {
    default:
    case 0:
        argv[1] = "AND";
        lens[1] = sizeof("AND") - 1;
        break;
    case 1:
        argv[1] = "OR";
        lens[1] = sizeof("OR") - 1;
        break;
    case 2:
        argv[1] = "NOT";
        lens[1] = sizeof("NOT") - 1;
        break;
    case 3:
        argv[1] = "XOR";
        lens[1] = sizeof("XOR") - 1;
        break;
    }
    argv[2] = const_cast<c8*>(key);
    lens[2] = keyLen;
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


bool CRedisRequest::bitfiled(const c8* key, u32 keyLen,
    const c8** val, const u32* valLens, u32 count) {
    if (nullptr == key || 0 == keyLen || nullptr == val || 0 == valLens
        || 0 == count) {
        return false;
    }
    const u32 start = 2;
    const u32 maxcache = 128;
    c8* tmp_argv[maxcache + start];
    u32 tmp_size[maxcache + start];
    const u32 cnt = start + count;
    c8** argv = count > maxcache ? new c8*[cnt] : tmp_argv;
    u32* lens = count > maxcache ? new u32[cnt] : tmp_size;

    argv[0] = "BITFIELD";
    lens[0] = sizeof("BITFIELD") - 1;
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

} //namespace db {
} // namespace irr
