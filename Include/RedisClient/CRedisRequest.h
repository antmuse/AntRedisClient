#pragma once
#include "CRedisCommand.h"

namespace irr {
namespace db {

class CRedisRequest : public CRedisCommand {
public:
    CRedisRequest();
    ~CRedisRequest();

    //---------------------------------cluster---------------------------------
    bool clusterInfo();
    bool clusterNodes();
    bool clusterSlots();

    //---------------------------------connect---------------------------------
    bool auth(const c8* passowrd);
    bool echo(const c8* msg);
    bool select(s32 dbID);
    bool ping();
    bool quit();
    bool shutdown();

    //---------------------------------key---------------------------------
    bool del(const c8* key);
    bool del(const c8* key, u32 kenLen);

    bool unlink(const c8* key);
    bool unlink(const c8* key, u32 kenLen);

    bool ttl(const c8* key);
    bool ttl(const c8* key, u32 kenLen);

    bool pttl(const c8* key);
    bool pttl(const c8* key, u32 kenLen);

    bool objectRefcount(const c8* key);
    bool objectRefcount(const c8* key, u32 keyLen);
    bool objectEncoding(const c8* key);
    bool objectEncoding(const c8* key, u32 keyLen);
    bool objectIdletime(const c8* key);
    bool objectIdletime(const c8* key, u32 keyLen);

    bool type(const c8* key);
    bool type(const c8* key, u32 kenLen);

    bool dump(const c8* key);
    bool dump(const c8* key, u32 kenLen);

    bool randomkey();

    /**
    * @brief rename key1 to key2.
    */
    bool rename(const c8* key1, const c8* key2);
    bool rename(const c8* key1, u32 kenLen1, const c8* key2, u32 kenLen2);

    bool renamenx(const c8* key1, const c8* key2);
    bool renamenx(const c8* key1, u32 kenLen1, const c8* key2, u32 kenLen2);

    /**
    * @param timeout in seconds.
    */
    bool expire(const c8* key, u32 timeout);
    bool expire(const c8* key, u32 kenLen, u32 timeout);

    bool move(const c8* key, u32 destDB);
    bool move(const c8* key, u32 kenLen, u32 destDB);

    /**
    * @param timeout in milliseconds.
    */
    bool pexpire(const c8* key, u32 timeout);
    bool pexpire(const c8* key, u32 kenLen, u32 timeout);

    bool pexpireat(const c8* key, s64 timestamp);
    bool pexpireat(const c8* key, u32 kenLen, s64 timestamp);

    /**
    * @brief �� UNIX ʱ������� KEY ����������
    * set the expiration for a key as a UNIX timestamp
    * @param timestamp UNIX ʱ��أ����� 1970 ������������
    */
    bool expireat(const c8* key, s64 timestamp);
    bool expireat(const c8* key, u32 kenLen, s64 timestamp);

    bool exists(const c8* key);
    bool exists(const c8* key, u32 kenLen);

    bool keys(const c8* key);
    bool keys(const c8* key, u32 kenLen);

    bool persist(const c8* key);
    bool persist(const c8* key, u32 kenLen);

    bool restore(const c8* key, u32 keyLen, const c8* key2, u32 keyLen2, s32 ttl, bool replace);

    bool scan(u32 offset, const c8* pattern, u32 patLen, u32 count = 0);

    /**
    * @brief MIGRATE host port key destination-db timeout [COPY] [REPLACE]
    * @param flag c=[COPY] r=[REPLACE] 0=default
    * eg: MIGRATE 127.0.0.1 8899 greeting 0 1000
    */
    bool migrate(const c8* ip, u16 port, const c8* key, u32 keyLen, u32 destDB, u32 timeout, c8 flag = 0);





    //---------------------------------list---------------------------------
    bool lset(const c8* key, u32 keyLen, u32 pos, const c8* val, u32 valLen);
    bool lindex(const c8* key, u32 keyLen, u32 pos);

    //LINSERT key BEFORE|AFTER pivot value
    bool linsert(const c8* key, u32 keyLen, const c8* pivot, u32 pivotLen,
        const c8* val, u32 valLen, bool after);

    bool lrem(const c8* key, u32 keyLen, s32 pos, const c8* val, u32 valLen);
    bool ltrim(const c8* key, u32 keyLen, s32 start, s32 end);

    bool lpush(const c8* key, u32 keyLen, const c8* val, u32 valLen);
    bool rpush(const c8* key, u32 keyLen, const c8* val, u32 valLen);

    bool lpushx(const c8* key, u32 keyLen, const c8* val, u32 valLen);
    bool rpushx(const c8* key, u32 keyLen, const c8* val, u32 valLen);

    bool rpoplpush(const c8* key, u32 keyLen, const c8* val, u32 valLen);
    bool brpoplpush(const c8* key, u32 keyLen, const c8* val, u32 valLen);

    bool lpop(const c8* key, u32 keyLen);
    bool rpop(const c8* key, u32 keyLen);

    bool blpop(const c8* key, u32 keyLen);
    bool brpop(const c8* key, u32 keyLen);

    bool llen(const c8* key, u32 keyLen);
    bool lrange(const c8* key, u32 keyLen, s32 start, s32 end);


    //---------------------------------string---------------------------------
    bool set(const c8* key, const c8* value);
    bool set(const c8* key, u32 kenLen, const c8* value, u32 valLen);
    bool mset(const c8** key, const u32* keyLen, u32 count);
    bool msetnx(const c8** key, const u32* keyLen, u32 count);
    bool mget(const c8** key, const u32* keyLen, u32 count);
    bool getset(const c8* key, u32 kenLen, const c8* value, u32 valLen);
    bool setnx(const c8* key, u32 kenLen, const c8* value, u32 valLen);
    bool setex(const c8* key, u32 kenLen, const c8* value, u32 valLen, u32 timeout);
    bool psetex(const c8* key, u32 kenLen, const c8* value, u32 valLen, u32 timeout);
    bool get(const c8* key);
    bool get(const c8* key, u32 keyLen);
    bool incr(const c8* key, u32 keyLen);
    bool decr(const c8* key, u32 keyLen);
    bool incrby(const c8* key, u32 keyLen, s32 addon);
    bool incrbyfloat(const c8* key, u32 keyLen, f64 addon);
    bool decrby(const c8* key, u32 keyLen, s32 addon);
    bool stringlen(const c8* key, u32 keyLen);
    bool append(const c8* key, u32 keyLen, const c8* value, u32 valLen);
    bool setrange(const c8* key, u32 kenLen, const c8* value, u32 valLen, u32 offset);
    bool getrange(const c8* key, u32 keyLen, s32 start, s32 end);




private:
};


} //namespace db {
} // namespace irr

