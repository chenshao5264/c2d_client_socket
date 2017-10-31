#include "BSDSocket.h"

#if (CC_PLATFORM_WIN32 == CC_PLATFORM_WIN32)
static bool isStartup = false;
#endif

BSDSocket::BSDSocket()
    : m_uSocket(INVALID_SOCKET)
{
    
}

BSDSocket::~BSDSocket()
{
}

bool BSDSocket::init()
{
#if (CC_PLATFORM_WIN32 == CC_PLATFORM_WIN32)
    if (!isStartup)
    {
        WSADATA wsaData;
        int nRet = WSAStartup(MAKEWORD(2, 0), &wsaData);
        if (nRet)
        {
            CCLOGERROR("WSAStartup failed!");
            return false;
        }
        isStartup = true;
    }
#endif

    if (m_uSocket != INVALID_SOCKET)
    {
        this->close();
    }

    m_uSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_uSocket == INVALID_SOCKET)
    {
        CCLOGERROR("create socket failed");
        return false;
    }
   
/*
#if( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
    unsigned int ul = 1; // 0为阻塞模式，1为非阻塞
    int nRet = ioctlsocket(m_uSocket, FIONBIO, (u_long*)&ul);
    if (nRet == SOCKET_ERROR)
    {
        CCLOGERROR("set unblocking failed");
        this->close();
        return false;
    }
#else
    int nFlags = fcntl(m_uSocket, F_GETFL, 0);
    int nRet = fcntl(m_uSocket, F_SETFL, nFlags | O_NONBLOCK); // 设置非阻塞
    if (nRet == SOCKET_ERROR)
    {
        CCLOGERROR("set unblocking failed");
        this->close();
        return false;
    }
#endif
*/
    int nNoDelay = 1;
    if (setsockopt(m_uSocket, IPPROTO_TCP, TCP_NODELAY, (char*)&nNoDelay, sizeof(nNoDelay)) == SOCKET_ERROR)
    {
        CCLOGERROR("set nodelay failed");
        this->close();
        return false;
    }

    return true;
}

int BSDSocket::read(char * buff, int len)
{
    if (m_uSocket == INVALID_SOCKET)
    {
        return eSocketIoError;
    }
    return ::recv(m_uSocket, buff, len, 0);
}

int BSDSocket::write(char * buff, int len)
{
    if (m_uSocket == INVALID_SOCKET)
    {
        return eSocketIoError;
    }
        
#if( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
    return ::send(m_uSocket, buff, len, 0);
#else
    return ::send(m_uSocket, buff, len, SO_NOSIGPIPE);
#endif
}

ESocketStatus BSDSocket::getSocketStatus()
{
    if (m_uSocket == INVALID_SOCKET)
    {
        return eSocketIoError;
    }

    fd_set fd;
    FD_ZERO(&fd);
    FD_SET(m_uSocket, &fd);
    
    struct timeval tv;
    tv.tv_sec  = 0;
    tv.tv_usec = 0;

    if (select((int)(m_uSocket + 1), nullptr, &fd, nullptr, &tv) > 0)
    {
        if (FD_ISSET(m_uSocket, &fd))
        {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
            return eSocketConnected;
#else
            int nError;
            socklen_t len = sizeof(nError);
            if (getsockopt(m_uSocket, SOL_SOCKET, SO_ERROR, &nError, &len) < 0)
            {
                return eSocketConnectFailed;
            }
            if (nError == ECONNREFUSED || nError == ETIMEDOUT)
            {
                return eSocketConnectFailed;
            }
            return eSocketConnected;
#endif
        }
    }

    return eSocketConnecting;
}

bool BSDSocket::isVaild(bool isRead)
{
    return isSocketVaid(m_uSocket, isRead);
}

void BSDSocket::close()
{
    if (m_uSocket == INVALID_SOCKET)
    {
        return;
    }

#if( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
    closesocket(m_uSocket);
#else
    close(m_uSocket);
#endif
    m_uSocket = INVALID_SOCKET;
}

bool BSDSocket::connect(const char* ip, unsigned short port)
{
    
    if (m_uSocket == INVALID_SOCKET)
    {
        if (!init())
        {
            return false;
        }
    }

    //连接ip
    struct sockaddr_in svraddr;
    svraddr.sin_family      = AF_INET;
    svraddr.sin_addr.s_addr = inet_addr(ip);
    svraddr.sin_port        = ::htons(port);
    int nRet = ::connect(m_uSocket, (struct sockaddr*) &svraddr, sizeof(svraddr));
    if (nRet == SOCKET_ERROR)
    {
        return false;
    }
    return true;

    /*
#if( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
    int nError = WSAGetLastError();
    if (nError == WSAEWOULDBLOCK)
    {
        return true;
    }
    else
    {
        return false;
    }
#else
    if (nRet == SOCKET_ERROR && errno == EINPROGRESS)
    {
        return true;
    }
    else
    {
        return false;
    }
#endif

    return false;*/
}

void BSDSocket::disconnect()
{
    if (m_uSocket == INVALID_SOCKET)
    {
        return;
    }

    this->close();
}

