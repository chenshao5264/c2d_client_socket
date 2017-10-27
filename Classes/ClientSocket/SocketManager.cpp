#include "SocketManager.h"

#include "BSDSocket.h"
#include "NetMacros.h"

static SocketManager *s_pSocketManager = nullptr;

SocketManager::SocketManager()
{
    
}

SocketManager::~SocketManager()
{
}

SocketManager * SocketManager::getInstnace()
{
    if (!s_pSocketManager)
    {
        s_pSocketManager = new (std::nothrow) SocketManager();
        s_pSocketManager->init();
    }
    return nullptr;
}

bool SocketManager::init()
{
    cocos2d::Director::getInstance()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(SocketManager::runSchedule), this, 0.0f, false);
    return true;
}

void SocketManager::connect(const char * ip, unsigned short port, ESocketType eScoketType /*= eSocketTypeLogin*/)
{
    auto iter = m_mapName2Socket.find(eSocketTypeLogin);
    if (iter != m_mapName2Socket.cend())
    {
        CCLOG("ip = %s: %u has connected!", ip, port);
        return;
    }

    auto uSocket = new BSDSocket();
    bool isSuc = uSocket->connect(ip, port);
    if (isSuc)
    {
        m_mapName2Socket.insert(std::pair<ESocketType, BSDSocket*>(eSocketTypeLogin, uSocket));
    }
    else
    {
        delete uSocket;
    }
}

void SocketManager::runSchedule(float dt)
{

}
