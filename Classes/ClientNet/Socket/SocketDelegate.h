#ifndef __SocketDelegate_H__
#define __SocketDelegate_H__

#include "cocos2d.h"

#include "Public/Singleton.h"

/*
    单列的socket委托类
*/
class SocketDelegate : public CSingleton<SocketDelegate>
{
public:
    SocketDelegate();
    ~SocketDelegate();

    void onConnectTimeout();

    void onConnected();

    void onDisconnected();

    void onError();

    void onMessage(char* pData);
};


#define SOCKET_DELEGATE_INSTANCE SocketDelegate::getInstance()

#endif
