#ifndef __SocketManager_H__
#define __SocketManager_H__

#include <map>
#include "cocos2d.h"

enum ESocketType
{
    eSocketTypeLogin = 0,
    eSocketTypeLobby,
    eSocketTypeGame,
};

class BSDSocket;

class SocketManager : cocos2d::Ref
{
private:
    SocketManager();
    bool init();

public:
    ~SocketManager();
    static SocketManager* getInstnace();
    
    void connect(const char* ip, unsigned short port, ESocketType eScoketType = eSocketTypeLogin);

private:
    void runSchedule(float dt);

public:
    std::map<ESocketType, BSDSocket*> m_mapName2Socket;
};

#endif