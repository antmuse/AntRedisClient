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
    * @brief 用 UNIX 时间截设置 KEY 的生存周期
    * set the expiration for a key as a UNIX timestamp
    * @param timestamp UNIX 时间截，即自 1970 年以来的秒数
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


    //---------------------------------set---------------------------------
    bool sdiff(const c8** keys, const u32* keyLens, u32 count);
    bool sdiffstore(const c8* destKey, u32 destKeyLen, const c8** keys, const u32* keyLens, u32 count);
    bool sunion(const c8** keys, const u32* keyLens, u32 count);
    bool sunionstore(const c8* destKey, u32 destKeyLen, const c8** keys, const u32* keyLens, u32 count);
    bool sinter(const c8** keys, const u32* keyLens, u32 count);
    //SINTERSTORE
    bool sinterstore(const c8* destKey, u32 destKeyLen, const c8** keys, const u32* keyLens, u32 count);
    bool sadd(const c8* key, u32 keyLen, const c8* val, const u32 valLens);
    bool sadd(const c8* key, u32 keyLen, const c8** val, const u32* valLens, u32 count);
    //SISMEMBER key member
    bool sismember(const c8* key, u32 keyLen, const c8* val, const u32 valLens);
    bool spop(const c8* key, u32 keyLen);
    bool scard(const c8* key, u32 keyLen);
    bool smembers(const c8* key, u32 keyLen);
    //SRANDMEMBER key [count]
    bool srandmember(const c8* key, u32 keyLen, u32 count = 0);
    bool srem(const c8* key, u32 keyLen, const c8* val, const u32 valLens);
    bool srem(const c8* key, u32 keyLen, const c8** val, const u32* valLens, u32 count);
    bool smove(const c8* key1, u32 keyLen1, const c8* key2, u32 keyLen2, const c8* val, const u32 valLen);
    bool sscan(const c8* key, u32 keyLen, u32 offset, const c8* pattern, u32 patLen, u32 count = 0);


    //---------------------------------zset---------------------------------
    /*
    * @brief ZADD key score member [[score member] [score member] …]
    */
    bool zadd(const c8* key, u32 keyLen, const c8** val, const u32* valLens, u32 count);
    bool zscore(const c8* key, u32 keyLen, const c8* val, const u32 valLens);
    //ZINCRBY key increment member
    bool zincrby(const c8* key, u32 keyLen, const c8* val, const u32 valLens, s32 value);
    bool zcard(const c8* key, u32 keyLen);
    //ZCOUNT key min max
    bool zcount(const c8* key, u32 keyLen, s32 min, s32 max);
    //ZRANGE key start stop [WITHSCORES]
    bool zrange(const c8* key, u32 keyLen, s32 start, s32 stop, bool withScore = false);
    bool zrevrange(const c8* key, u32 keyLen, s32 start, s32 stop, bool withScore = false);
    /**
    * @brief ZRANGEBYSCORE key min max [WITHSCORES] [LIMIT offset count]
    * @param flag 位开关 1: >min, 2: -inf, 3: <max, 4: +inf
    */
    bool zrangebyscore(const c8* key, u32 keyLen, f32 min, f32 max, u32 flag = 0, bool withScore = false);
    //ZREVRANGEBYSCORE key max min [WITHSCORES] [LIMIT offset count]
    bool zrevrangebyscore(const c8* key, u32 keyLen, f32 min, f32 max, u32 flag = 0, bool withScore = false);
    bool zrank(const c8* key, u32 keyLen, const c8* val, const u32 valLens);
    bool zrevrank(const c8* key, u32 keyLen, const c8* val, const u32 valLens);
    bool zrem(const c8* key, u32 keyLen, const c8** val, const u32* valLens, u32 count);
    //ZREMRANGEBYRANK key start stop
    bool zremrangebyrank(const c8* key, u32 keyLen, s32 start, s32 stop);
    //ZREMRANGEBYSCORE key min max
    bool zremrangebyscore(const c8* key, u32 keyLen, f32 min, f32 max, u32 flag = 0);
    //ZRANGEBYLEX key min max [LIMIT offset count]
    bool zrangebylex(const c8* key, u32 keyLen, const c8* min, u32 minLen, const c8* max, u32 maxLen);
    //ZLEXCOUNT key min max
    bool zlexcount(const c8* key, u32 keyLen, const c8* min, u32 minLen, const c8* max, u32 maxLen);
    //ZREMRANGEBYLEX key min max
    bool zremrangebylex(const c8* key, u32 keyLen, const c8* min, u32 minLen, const c8* max, u32 maxLen);
    //ZSCAN key cursor [MATCH pattern] [COUNT count]
    //TODO>>

    //---------------------------------hash---------------------------------
    bool hset(const c8* key, u32 keyLen, const c8* name, u32 nameLen, const c8* value, u32 valLen);
    bool hsetnx(const c8* key, u32 keyLen, const c8* name, u32 nameLen, const c8* value, u32 valLen);
    bool hget(const c8* key, u32 keyLen, const c8* name, u32 nameLen);
    bool hgetall(const c8* key, u32 keyLen);
    bool hexists(const c8* key, u32 keyLen, const c8* name, u32 nameLen);
    bool hdel(const c8* key, u32 keyLen, const c8* name, u32 nameLen);
    bool hlen(const c8* key, u32 keyLen);
    bool hstrlen(const c8* key, u32 keyLen, const c8* name, u32 nameLen);
    bool hincrby(const c8* key, u32 keyLen, const c8* name, u32 nameLen, s32 val);
    bool hincrbyfloat(const c8* key, u32 keyLen, const c8* name, u32 nameLen, f32 val);
    bool hkeys(const c8* key, u32 keyLen);
    bool hvals(const c8* key, u32 keyLen);
    bool hscan(const c8* key, u32 keyLen, u32 offset, const c8* pattern, u32 patLen, u32 count = 0);
    bool hmset(const c8* key, u32 keyLen, const c8** pairs, const u32* pairLens, u32 count);
    bool hmget(const c8* key, u32 keyLen, const c8** name, const u32* nameLen, u32 count);


private:
};


} //namespace db {
} // namespace irr

