#include "TCPSocket.h"

#include "BSDSocket.h"
#include "SocketDelegate.h"

#include "Crypto.h"

using namespace cocos2d;

TCPSocket::TCPSocket()
    : m_eSocketStatus(eSocketIoClosed)
    , m_pDelegate(nullptr)
    , m_fHeartElapsedTime(.0f)
    , m_fConnectingElapsedTime(.0f)
    , m_pReadBuffer(new char[SOCKET_READ_BUFFER_SIZE])
    //, m_pSendBuffer(new char[SOCKET_READ_BUFFER_SIZE])
    , m_iSendSize(0)
    , m_pIP(nullptr)
    , m_iPort(0)
{
}

TCPSocket::~TCPSocket()
{
    delete[] m_pReadBuffer;
    //delete[] m_pSendBuffer;

    m_pSocket->close();
    Director::getInstance()->getScheduler()->unschedule(CC_SCHEDULE_SELECTOR(TCPSocket::onRunSchedule), this);
}

bool TCPSocket::init()
{
    Director::getInstance()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(TCPSocket::onRunSchedule), this, 0, false);

    return true;
}

void TCPSocket::setDelegate(SocketDelegate * delegate)
{
    m_pDelegate = delegate;
}

void TCPSocket::connect(const char * ip, unsigned short port)
{
    m_iSendSize = 0;
    if (m_eSocketStatus != eSocketConnected && m_eSocketStatus != eSocketConnecting)
    {
        m_pSocket = new (std::nothrow) BSDSocket();
        m_pSocket->init();
        if (m_pSocket->connect(ip, port))
        {
            m_eSocketStatus = eSocketConnecting;
            m_pIP = const_cast<char*>(ip);
            m_iPort = port;
        }
        else
        {
            if (m_pDelegate)
            {
                m_pDelegate->onError();
            }
        }
    }
}

void TCPSocket::reConnect()
{
    if (m_eSocketStatus == eSocketConnecting || m_eSocketStatus == eSocketConnected)
    {
        CCLOG("socketed is connecting! or socketed is connected!");
        return;
    }

    CCLOG("try reConnect!");
    this->connect(m_pIP, m_iPort);
}

void TCPSocket::send(const char * pData)
{
    if (m_eSocketStatus != eSocketConnected)
    {
        return;
    }

    if (m_pSocket->isVaild(false))
    {
        this->doWrite(pData);
    }
}

void TCPSocket::onRunSchedule(float dt)
{
    if (m_eSocketStatus == eSocketConnecting)
    {
        ESocketStatus status = m_pSocket->getSocketStatus();
        if (status == eSocketConnecting)
        {
            if (m_fConnectingElapsedTime >= CONNECTING_TIMEOUT)
            {
                m_pSocket->disconnect();
                m_eSocketStatus = eSocketDisconnected;
                m_fConnectingElapsedTime = .0f;
                
                if (m_pDelegate)
                {
                    m_pDelegate->onConnectTimeout();
                }
            } 
            else
            {
                m_fConnectingElapsedTime += dt;
            }
        } 
        else if (status == eSocketConnectFailed)
        {
            m_eSocketStatus = eSocketConnectFailed;
            if (m_pDelegate)
            {
                m_pDelegate->onConnected();
            }
        } 
        else if (status == eSocketConnected)
        {
            m_eSocketStatus = eSocketConnected;
            if (m_pDelegate)
            {
                m_pDelegate->onConnected();
            }
        } 
        else
        {

        }
    }
    else if (m_eSocketStatus == eSocketConnected)
    {
        if (m_pSocket->isVaild(true))
        {
            if (!this->doRead())
            {
                return;
            }
        }
    }
}

bool TCPSocket::doRead()
{
    memset(m_pReadBuffer, 0, SOCKET_READ_BUFFER_SIZE);
    int nRet = m_pSocket->read(m_pReadBuffer, SOCKET_READ_BUFFER_SIZE);
    if (nRet == eSocketIoError || nRet == eSocketIoClosed)
    {
        m_pSocket->close();
        m_eSocketStatus = eSocketIoClosed;
        if (m_pDelegate)
        {
            m_pDelegate->onDisconnected();
            return false;
        }
    }
    else 
    {
        if (m_pDelegate)
        {
            // 拆包（返序列化）

            // 解密
            char* decryptBuf = nullptr;
            Crypto::decrypt(m_pReadBuffer, strlen(m_pReadBuffer), &decryptBuf);

            m_pDelegate->onMessage(decryptBuf);
        }
    }
    return true;
}

bool TCPSocket::doWrite(const char* pData)
{
    // 打包（序列化）


    // 加密
    char* encryptBuf = nullptr;
    Crypto::encrypt(pData, strlen(pData), &encryptBuf);

    int nRet = m_pSocket->write(encryptBuf, strlen(encryptBuf));
    if (nRet == eSocketIoError)
    {
        m_pSocket->close();
        m_eSocketStatus = eSocketIoClosed;
        if (m_pDelegate)
        {
            m_pDelegate->onDisconnected();
        }
        return false;
    } 

    return true;
}
