#ifndef __SocketDelegate_H__
#define __SocketDelegate_H__

#include "cocos2d.h"

#include "Public/Singleton.h"

/*
    ���е�socketί����
*/
class SocketDelegate : public CSingleton<SocketDelegate>
{
    FRIEND_SINGLETON_CLASS(SocketDelegate);
private:
    SocketDelegate();
public:
    
    ~SocketDelegate();

    // ��ʱ�ص�
    void onConnectTimeout();

    void onConnected();

    void onDisconnected();

    void onError();

    // ������Ϣ�ص�
    void onMessage(char* pData);
};


#define SOCKET_DELEGATE_INSTANCE SocketDelegate::getInstance()

#endif
