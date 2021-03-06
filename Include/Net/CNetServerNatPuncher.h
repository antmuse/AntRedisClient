#ifndef APP_CNETSERVERNATPUNCHER_H
#define APP_CNETSERVERNATPUNCHER_H

#include "AppMap.h"
#include "INetServer.h"
#include "IRunnable.h"
#include "CNetSocket.h"

namespace app {
class CThread;

namespace net {

class CNetServerNatPuncher : public IRunnable {
public:
    CNetServerNatPuncher();

    virtual ~CNetServerNatPuncher();

    virtual void run()override;

    bool start();

    bool stop();

    void setLocalAddress(const CNetAddress& it) {
        mAddressLocal = it;
    }

    const CNetAddress& getLocalAddress() const {
        return mAddressLocal;
    }

private:
    struct SClientNode {
        u64 mTime;
        //u32 mLocalIP;
        //u16 mLocalPort;
        CNetAddress mAddress;
    };

    const core::TMap<CNetAddress::ID, SClientNode*>::Node* getAnyRemote(CNetAddress::ID& my)const;
    const core::TMap<CNetAddress::ID, SClientNode*>::Node* getRemote(CNetAddress::ID& my)const;
    void checkTimeout();
    void removeAllClient();
    bool initialize();
    void removeAll();
    bool clearError();

    bool mRunning;                  ///<True if server started, else false
    u32 mOverTimeInterval;
    u64 mCurrentTime;
    core::TMap<CNetAddress::ID, SClientNode*>  mAllClient;
    CNetSocket mConnector;
    CNetAddress mAddressRemote;
    CNetAddress mAddressLocal;
    CThread* mThread;
};


} //namespace net
} //namespace app

#endif //APP_CNETSERVERNATPUNCHER_H
