#include "CRedisRequest.h"

namespace app {
namespace db {

bool CRedisRequest::publish(const s8* key, u32 keyLen, const s8* val, const u32 valLen) {
    if (nullptr == key || 0 == keyLen || nullptr == val || 0 == valLen) {
        return false;
    }
    const u32 cnt = 3;
    const s8* argv[cnt];
    u32 lens[cnt];
    argv[0] = "PUBLISH";
    lens[0] = sizeof("PUBLISH") - 1;
    argv[1] = key;
    lens[1] = keyLen;
    argv[2] = val;
    lens[2] = valLen;
    bool ret;
    if (isClusterMode()) {
        ret = launch(hashSlot(key, keyLen), cnt, const_cast<const s8**>(argv), lens);
    } else {
        ret = launch(cnt, const_cast<const s8**>(argv), lens);
    }
    return ret;
}


bool CRedisRequest::subscribe(const s8** val, const u32* valLens, u32 count) {
    if (nullptr == val || 0 == valLens || 0 == count) {
        return false;
    }
    const u32 start = 1;
    const u32 maxcache = 128;
    s8* tmp_argv[maxcache + start];
    u32 tmp_size[maxcache + start];
    const u32 cnt = start + count;
    s8** argv = count > maxcache ? new s8*[cnt] : tmp_argv;
    u32* lens = count > maxcache ? new u32[cnt] : tmp_size;

    argv[0] = "SUBSCRIBE";
    lens[0] = sizeof("SUBSCRIBE") - 1;
    for (u32 i = 0; i < count; ++i) {
        argv[i + start] = const_cast<s8*>(val[i]);
        lens[i + start] = valLens[i];
    }

    bool ret = launch(cnt, const_cast<const s8**>(argv), lens);
    if (count > maxcache) {
        delete[] argv;
        delete[] lens;
    }
    return ret;
}


bool CRedisRequest::unsubscribe(const s8** val, const u32* valLens, u32 count) {
    const u32 start = 1;
    const u32 maxcache = 128;
    s8* tmp_argv[maxcache + start];
    u32 tmp_size[maxcache + start];
    u32 cnt = start + count;
    s8** argv = count > maxcache ? new s8*[cnt] : tmp_argv;
    u32* lens = count > maxcache ? new u32[cnt] : tmp_size;

    argv[0] = "UNSUBSCRIBE";
    lens[0] = sizeof("UNSUBSCRIBE") - 1;
    const bool valid = nullptr != val && 0 != valLens && count > 0;
    if (valid) {
        for (u32 i = 0; i < count; ++i) {
            argv[i + start] = const_cast<s8*>(val[i]);
            lens[i + start] = valLens[i];
        }
    } else {
        cnt = 1;
    }

    bool ret = launch(cnt, const_cast<const s8**>(argv), lens);
    if (count > maxcache) {
        delete[] argv;
        delete[] lens;
    }
    return ret;
}


bool CRedisRequest::psubscribe(const s8** val, const u32* valLens, u32 count) {
    if (nullptr == val || 0 == valLens || 0 == count) {
        return false;
    }
    const u32 start = 1;
    const u32 maxcache = 128;
    s8* tmp_argv[maxcache + start];
    u32 tmp_size[maxcache + start];
    const u32 cnt = start + count;
    s8** argv = count > maxcache ? new s8*[cnt] : tmp_argv;
    u32* lens = count > maxcache ? new u32[cnt] : tmp_size;

    argv[0] = "PSUBSCRIBE";
    lens[0] = sizeof("PSUBSCRIBE") - 1;
    for (u32 i = 0; i < count; ++i) {
        argv[i + start] = const_cast<s8*>(val[i]);
        lens[i + start] = valLens[i];
    }

    bool ret = launch(cnt, const_cast<const s8**>(argv), lens);
    if (count > maxcache) {
        delete[] argv;
        delete[] lens;
    }
    return ret;
}


bool CRedisRequest::punsubscribe(const s8** val, const u32* valLens, u32 count) {
    const u32 start = 1;
    const u32 maxcache = 128;
    s8* tmp_argv[maxcache + start];
    u32 tmp_size[maxcache + start];
    u32 cnt = start + count;
    s8** argv = count > maxcache ? new s8*[cnt] : tmp_argv;
    u32* lens = count > maxcache ? new u32[cnt] : tmp_size;

    argv[0] = "PUNSUBSCRIBE";
    lens[0] = sizeof("PUNSUBSCRIBE") - 1;
    const bool valid = nullptr != val && 0 != valLens && count > 0;
    if (valid) {
        for (u32 i = 0; i < count; ++i) {
            argv[i + start] = const_cast<s8*>(val[i]);
            lens[i + start] = valLens[i];
        }
    } else {
        cnt = 1;
    }

    bool ret = launch(cnt, const_cast<const s8**>(argv), lens);
    if (count > maxcache) {
        delete[] argv;
        delete[] lens;
    }
    return ret;
}


} //namespace db {
} // namespace app
