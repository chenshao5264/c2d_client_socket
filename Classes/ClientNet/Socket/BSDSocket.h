#ifndef __BSDSocket_H__
#define __BSDSocket_H__

#include "NetMacros.h"

class BSDSocket
{
public:
    BSDSocket();
    ~BSDSocket();

    bool init();
    int read(char* buff, int len);
    int write(char* buff, int len);
    void close();
    bool connect(const char* ip, unsigned short port);
    void disconnect();
    ESocketStatus getSocketStatus();

    bool isVaild(bool isRead = false);

private:
    SOCKET m_uSocket;
};

#endif