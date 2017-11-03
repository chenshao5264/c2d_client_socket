#ifndef __TCPManager_H__
#define __TCPManager_H__

#include "Public/Singleton.h"

class TCPSocket;

class TCPManager : public CSingleton<TCPManager>
{
    FRIEND_SINGLETON_CLASS(TCPManager);
private:
    TCPManager();
public:
    ~TCPManager();

    // socket1
    void makeConnect1(const char* ip, unsigned short port);
    void disconnect1();

    // 发送游戏操作请求
    void sendLoginReq();

public:
    TCPSocket* m_pTCPSocket1;
};

#endif
