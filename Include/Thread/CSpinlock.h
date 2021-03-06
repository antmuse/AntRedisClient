#ifndef APP_CSPINLOCK_H
#define APP_CSPINLOCK_H

#include "HConfig.h"

namespace app {

/**
* @brief a spinlock base on atomic operations.
* @note Do't use spinlock on mononuclear CPU, or havy calculation tasks.
* CSpinlock is not recursive lock.
*/
class CSpinlock {
public:
    CSpinlock();

    ~CSpinlock();

    /**
    * @brief spinlock.
    * @note It's a busing CPU wait when spin.
    */
    void lock();

    /**
    * @brief try spinlock.
    * @return false if can't locked, else true.
    */
    bool trylock();


    void unlock();

private:
    s32 mValue;
    CSpinlock(const CSpinlock& it) = delete;
    CSpinlock& operator=(const CSpinlock& it) = delete;
};



class CAutoSpinlock {
public:
    CAutoSpinlock(CSpinlock& it) : mLock(it) {
        mLock.lock();
    }

    ~CAutoSpinlock() {
        mLock.unlock();
    }

private:
    CSpinlock& mLock;
};


} //namespace app

#endif //APP_CSPINLOCK_H
