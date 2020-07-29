#pragma once
#include "HConfig.h"
#include "CMemoryHub.h"

namespace app {
namespace db {

class CRedisRequest;
class CRedisResponse;
class CRedisClient;

///A callable function pointer for RedisResult.
typedef void(*AppRedisCaller)(CRedisRequest* it, CRedisResponse*);

enum ERedisResultType {
    ERRT_NIL,   //NULL, not exist
    ERRT_ERROR = '-',
    ERRT_STRING = '+',
    ERRT_BULK_STR = '$',
    ERRT_INT = ':',
    ERRT_ARRAY = '*'
};

class CRedisResponse {
public:
    union SRedisValue {
        s64 mVal64;
        s8* mValStr;
        CRedisResponse** mNodes; //only for ERRT_ARRAY
    };
    SRedisValue mValue;
    u32 mUsed;
    u32 mAllocated;
    CMemoryHub& mHub;
    u8 mType;
    u8 mStatus; //@see EDecodeStatus

    CRedisResponse(CMemoryHub& it);
    ~CRedisResponse();

    void clear();

    s8* getStr()const {
        return mValue.mValStr;
    }

    s64 getS64()const {
        return mValue.mVal64;
    }

    bool isFinished()const {
        return EDS_DONE == mStatus;
    }

    bool isError()const {
        return (ERRT_ERROR == mType);
    }

    bool isOK()const {
        return (ERRT_STRING == mType && mValue.mValStr
            && (*(u16*)mValue.mValStr) == *(u16*)("OK"));
    }

    //eg: MOVED 153 127.0.0.1:3292
    bool isMoved() const {
        return (ERRT_ERROR == mType && mValue.mValStr
            && (*(u32*)mValue.mValStr) == *(u32*)("MOVE")
            && (*(u16*)(mValue.mValStr + sizeof(u32))) == *(u16*)("D "));
    }

    //eg: ASK 153 127.0.0.1:3292
    bool isAsk() const {
        return (ERRT_ERROR == mType && mValue.mValStr
            && (*(u32*)mValue.mValStr) == *(u32*)("ASK "));
    }

    /**
    * @brief decode a item in stream.
    * eg: stream is "+OK\r\n" or "$3\r\nabc\r\n"
    *     \p str point to the start of stream.
    *     \p len the position of stream's last '\n'(position start at 0).
    * @return the end position;
    */
    const s8* import(const s8* str, u64 len);

    void show(u32 level = 1, u32 index = 1)const;

    void makeError(const s8* str);

    CRedisResponse* getResult(u32 idx)const {
        if (ERRT_ARRAY != mType || EDS_DONE != mStatus || nullptr == mValue.mNodes) {
            return nullptr;
        }
        if (idx < mAllocated) {
            return mValue.mNodes[idx];
        }
        return nullptr;
    }

private:
    bool decodeSize(const s8 ch);

    enum EDecodeStatus {
        EDS_INIT = 0,
        EDS_INT,
        EDS_ARRAY,
        EDS_ARRAY_SIZE,
        EDS_STR,
        EDS_BULK_STR,
        EDS_BULK_SIZE,
        //EDS_TAIL,   // "\r\n"
        EDS_DONE = 0xFF
    };

    CRedisResponse(const CRedisResponse&) = delete;
    const CRedisResponse& operator=(const CRedisResponse&) = delete;
};


} //namespace db {
} // namespace app

