#ifndef __SocketDelegate_H__
#define __SocketDelegate_H__

#include "cocos2d.h"

#include "Public/Singleton.h"

/*
    单列的socket委托类
*/
class SocketDelegate : public CSingleton<SocketDelegate>
{
    FRIEND_SINGLETON_CLASS(SocketDelegate);
private:
    SocketDelegate();
public:
    
    ~SocketDelegate();

    // 超时回调
    void onConnectTimeout();

    void onConnected();

    void onDisconnected();

    void onError();

    // 接收消息回调
    void onMessage(char* pData);
};


#define SOCKET_DELEGATE_INSTANCE SocketDelegate::getInstance()

#endif
