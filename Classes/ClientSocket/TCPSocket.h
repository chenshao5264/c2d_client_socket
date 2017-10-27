#ifndef __TCPSocket_H__
#define __TCPSocket_H__

#include "cocos2d.h"

#include "NetMacros.h"


class BSDSocket;
class SocketDelegate;

class TCPSocket : public cocos2d::Ref
{
protected:
    TCPSocket();

public:
    virtual ~TCPSocket();

public:
    CREATE_FUNC(TCPSocket);
    bool init();

    void setDelegate(SocketDelegate* delegate);

    void connect(const char* ip, unsigned short port);

    /*
        重连上一次的ip
    */
    void reConnect();
    void send(const char* pData);
private:
    void onRunSchedule(float dt);
   
    bool doRead();
    bool doWrite(const char* pData);

private:
    SocketDelegate* m_pDelegate;
    BSDSocket*      m_pSocket;
    ESocketStatus   m_eSocketStatus;
   
    float m_fHeartElapsedTime;
    float m_fConnectingElapsedTime;

    char* m_pReadBuffer;
    //char* m_pSendBuffer;

    int m_iSendSize;

    char*            m_pIP;
    unsigned short   m_iPort;
};

#endif
