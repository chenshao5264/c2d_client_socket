#ifndef __SocketDelegate_H__
#define __SocketDelegate_H__

#include "cocos2d.h"

class SocketDelegate : public cocos2d::Ref
{
protected:
    SocketDelegate();

public:
    virtual ~SocketDelegate();

    CREATE_FUNC(SocketDelegate);
    bool init();

    virtual void onConnectTimeout();

    virtual void onConnected();

    virtual void onDisconnected();

    virtual void onError();

    virtual void onMessage(char* pData);
};

#endif
