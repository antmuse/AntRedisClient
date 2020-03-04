#include "CRedisRequest.h"

namespace irr {
namespace db {

bool CRedisRequest::geoadd(const c8* key, u32 keyLen, const c8** val, const u32* valLens, u32 count) {
    if (nullptr == key || 0 == keyLen || nullptr == val || 0 == valLens
        || 0 == count || 0 != count % 3) {
        return false;
    }
    const u32 start = 2;
    const u32 maxcache = 128;
    c8* tmp_argv[maxcache + start];
    u32 tmp_size[maxcache + start];
    const u32 cnt = start + count;
    c8** argv = count > maxcache ? new c8*[cnt] : tmp_argv;
    u32* lens = count > maxcache ? new u32[cnt] : tmp_size;

    argv[0] = "GEOADD";
    lens[0] = sizeof("GEOADD") - 1;

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

bool CRedisRequest::geodist(const c8* key, u32 keyLen,
    const c8* key1, u32 keyLen1,
    const c8* key2, u32 keyLen2, u32 unit) {
    if (nullptr == key || 0 == keyLen
        || nullptr == key1 || 0 == keyLen1
        || nullptr == key2 || 0 == keyLen2) {
        return false;
    }
    const u32 cnt = 5;
    const c8* argv[cnt];
    u32 lens[cnt];

    argv[0] = "GEODIST";
    lens[0] = sizeof("GEODIST") - 1;
    argv[1] = key;
    lens[1] = keyLen;
    argv[2] = key1;
    lens[2] = keyLen1;
    argv[3] = key2;
    lens[3] = keyLen2;
    switch (unit) {
    default:
    case 0:
        argv[4] = "m";
        lens[4] = sizeof("m") - 1;
        break;
    case 1:
        argv[4] = "km";
        lens[4] = sizeof("km") - 1;
        break;
    case 2:
        argv[4] = "mi";
        lens[4] = sizeof("mi") - 1;
        break;
    case 3:
        argv[4] = "ft";
        lens[4] = sizeof("ft") - 1;
        break;
    }

    bool ret;
    if (isClusterMode()) {
        ret = launch(hashSlot(key, keyLen), cnt, const_cast<const c8**>(argv), lens);
    } else {
        ret = launch(cnt, const_cast<const c8**>(argv), lens);
    }
    return ret;
}

bool CRedisRequest::geopos(const c8* key, u32 keyLen, const c8** val, const u32* valLens, u32 count) {
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

    argv[0] = "GEOPOS";
    lens[0] = sizeof("GEOPOS") - 1;

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


bool CRedisRequest::georadius(const c8* key, u32 keyLen,
    f32 posX, f32 posY, f32 redius, u32 max, u32 unit, u32 flag) {
    if (nullptr == key || 0 == keyLen) {
        return false;
    }
    if (posX > 180.0f || posX < 0.0f || posY > 90.0f || posY < 0.0f) {
        return false;
    }
    const u32 maxcache = 12;
    const c8* argv[maxcache];
    u32 lens[maxcache];

    argv[0] = "GEORADIUS";
    lens[0] = sizeof("GEORADIUS") - 1;
    argv[1] = key;
    lens[1] = keyLen;
    c8 longitude[32];
    c8 latitude[32];
    c8 rediustr[32];
    c8 count[16];
    argv[2] = longitude;
    lens[2] = snprintf(longitude, sizeof(longitude), "%.16f", posX);
    argv[3] = latitude;
    lens[3] = snprintf(latitude, sizeof(latitude), "%.16f", posY);
    argv[4] = rediustr;
    lens[4] = snprintf(rediustr, sizeof(rediustr), "%.16f", redius);
    switch (unit) {
    default:
    case 0:
        argv[5] = "m";
        lens[5] = sizeof("m") - 1;
        break;
    case 1:
        argv[5] = "km";
        lens[5] = sizeof("km") - 1;
        break;
    case 2:
        argv[5] = "mi";
        lens[5] = sizeof("mi") - 1;
        break;
    case 3:
        argv[5] = "ft";
        lens[5] = sizeof("ft") - 1;
        break;
    }
    u32 cnt = 6;
    //flag 1 = WITHCOORD, 2 = WITHDIST, 4 = WITHHASH, 8 = ASC | DESC
    if ((flag & 1) != 0) {
        argv[cnt] = "WITHCOORD";
        lens[cnt++] = sizeof("WITHCOORD") - 1;
    }
    if ((flag & 2) != 0) {
        argv[cnt] = "WITHDIST";
        lens[cnt++] = sizeof("WITHDIST") - 1;
    }
    if ((flag & 4) != 0) {
        argv[cnt] = "WITHHASH";
        lens[cnt++] = sizeof("WITHHASH") - 1;
    }
    if ((flag & 8) != 0) {
        argv[cnt] = "DESC";
        lens[cnt++] = sizeof("DESC") - 1;
    } else {
        argv[cnt] = "ASC";
        lens[cnt++] = sizeof("ASC") - 1;
    }
    if (max > 0) {
        argv[cnt] = "COUNT";
        lens[cnt++] = sizeof("COUNT") - 1;

        argv[cnt] = count;
        lens[cnt++] = snprintf(count, sizeof(count), "%u", max);
    }

    bool ret;
    if (isClusterMode()) {
        ret = launch(hashSlot(key, keyLen), cnt, const_cast<const c8**>(argv), lens);
    } else {
        ret = launch(cnt, const_cast<const c8**>(argv), lens);
    }
    return ret;
}


bool CRedisRequest::georadiusbymember(const c8* key, u32 keyLen,
    const c8* member, u32 memberLen,
    f32 redius, u32 max, u32 unit, u32 flag) {
    if (nullptr == key || 0 == keyLen || nullptr == member || 0 == memberLen) {
        return false;
    }
    const u32 maxcache = 11;
    const c8* argv[maxcache];
    u32 lens[maxcache];

    argv[0] = "GEORADIUSBYMEMBER";
    lens[0] = sizeof("GEORADIUSBYMEMBER") - 1;
    argv[1] = key;
    lens[1] = keyLen;
    c8 rediustr[32];
    c8 count[16];
    argv[2] = member;
    lens[2] = memberLen;
    argv[3] = rediustr;
    lens[3] = snprintf(rediustr, sizeof(rediustr), "%.16f", redius);
    switch (unit) {
    default:
    case 0:
        argv[4] = "m";
        lens[4] = sizeof("m") - 1;
        break;
    case 1:
        argv[4] = "km";
        lens[4] = sizeof("km") - 1;
        break;
    case 2:
        argv[4] = "mi";
        lens[4] = sizeof("mi") - 1;
        break;
    case 3:
        argv[4] = "ft";
        lens[4] = sizeof("ft") - 1;
        break;
    }
    u32 cnt = 5;
    //flag 1 = WITHCOORD, 2 = WITHDIST, 4 = WITHHASH, 8 = ASC | DESC
    if ((flag & 1) != 0) {
        argv[cnt] = "WITHCOORD";
        lens[cnt++] = sizeof("WITHCOORD") - 1;
    }
    if ((flag & 2) != 0) {
        argv[cnt] = "WITHDIST";
        lens[cnt++] = sizeof("WITHDIST") - 1;
    }
    if ((flag & 4) != 0) {
        argv[cnt] = "WITHHASH";
        lens[cnt++] = sizeof("WITHHASH") - 1;
    }
    if ((flag & 8) != 0) {
        argv[cnt] = "DESC";
        lens[cnt++] = sizeof("DESC") - 1;
    } else {
        argv[cnt] = "ASC";
        lens[cnt++] = sizeof("ASC") - 1;
    }
    if (max > 0) {
        argv[cnt] = "COUNT";
        lens[cnt++] = sizeof("COUNT") - 1;

        argv[cnt] = count;
        lens[cnt++] = snprintf(count, sizeof(count), "%u", max);
    }

    bool ret;
    if (isClusterMode()) {
        ret = launch(hashSlot(key, keyLen), cnt, const_cast<const c8**>(argv), lens);
    } else {
        ret = launch(cnt, const_cast<const c8**>(argv), lens);
    }
    return ret;
}


bool CRedisRequest::geohash(const c8* key, u32 keyLen, const c8** val, const u32* valLens, u32 count) {
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

    argv[0] = "GEOHASH";
    lens[0] = sizeof("GEOHASH") - 1;

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
