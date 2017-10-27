#ifndef __NetMacros_H__
#define __NetMacros_H__

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <windows.h>
#include <WS2tcpip.h>
typedef int socklen_t;
#else
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <sys/syscall.h>
#include <fcntl.h>
#include <netinet/tcp.h>

typedef unsigned int          SOCKET;
#define INVALID_SOCKET  (SOCKET)(~0)
#define SOCKET_ERROR            (-1)
#endif


#define SOCKET_SOTIMEOUT (5.0f)
#define SOCKET_READ_BUFFER_SIZE (20480)

#define CONNECTING_TIMEOUT (3.0f)
#define HEART_INTERVAL_TIME (3.0f)

enum ESocketStatus
{
    eSocketConnected      = 1,
    eSocketConnecting     = 2,
    eSocketDisconnected   = 3,
    eSocketConnectFailed  = 4,
    eSocketConnectTimeout = 5,
    eSocketIoClosed       = 0,
    eSocketIoError        = -1,
    eSocketCreateFailed   = -2,
};



static bool isSocketVaid(const SOCKET& uSocket, bool bRecive)
{
    if (uSocket == INVALID_SOCKET)
    {
        return false;
    }

    fd_set	fd;
    FD_ZERO(&fd);
    FD_SET(uSocket, &fd);

    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 0;

    if (!bRecive && select((int)(uSocket + 1), NULL, &fd, NULL, &tv) > 0)
    {
        if (FD_ISSET(uSocket, &fd))
        {
            return true;
        }
    }

    if (bRecive &&  select((int)(uSocket + 1), &fd, NULL, NULL, &tv) > 0)
    {
        if (FD_ISSET(uSocket, &fd))
        {
            return true;
        }
    }

    return false;
}

#endif
