#include "TCPManager.h"

#include "TCPSocket.h"
#include "SocketDelegate.h"
#include "ClientNet/MsgService/MsgPipe.h"

TCPManager::TCPManager()
    : m_pTCPSocket1(nullptr)
{
    MsgPipe::getInstance()->start();
}

TCPManager::~TCPManager()
{
    CC_SAFE_RELEASE(m_pTCPSocket1);
}

void TCPManager::makeConnect1(const char * ip, unsigned short port)
{
    if (m_pTCPSocket1)
    {
        return;
    }

    m_pTCPSocket1 = TCPSocket::create();
    if (!m_pTCPSocket1)
    {
        return;
    }

    m_pTCPSocket1->retain();
    m_pTCPSocket1->setDelegate(SOCKET_DELEGATE_INSTANCE);
    m_pTCPSocket1->connect(ip, port);
}

void TCPManager::disconnect1()
{
    CCLOG("disconnect socket1!");
    if (m_pTCPSocket1)
    {
        m_pTCPSocket1->disconnect();
        CC_SAFE_RELEASE(m_pTCPSocket1);
        m_pTCPSocket1 = nullptr;
    }
}

void TCPManager::sendLoginReq()
{
    if (!m_pTCPSocket1) 
    {
        return;
    }

    // test
    PACKET_DEMO req;
    req.day = 1;
    req.age = 99;
    req.dequeCards = { "deque1", "deque2", "deque3" };
    req.listCards = { "list1", "list2", "list3" };
    req.mapCards = { std::make_pair(1, "map1"), std::make_pair(2, "map2"), std::make_pair(3, "map3") };
    req.name = "≥Ω…Ÿ01";
    req.setCards = { "set1", "set2" };
    req.vecCards = { "vec1", "vec2", "vec3", "vec4" };

    // –Ú¡–ªØ
    CBuffer buf;
    buf << req;
    Pack pack(PACKET_DEMO_P, buf.getData(), buf.getLength());

    m_pTCPSocket1->send(pack);
}
