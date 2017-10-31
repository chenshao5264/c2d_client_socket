#include "SocketDelegate.h"

#include "ClientNet/NetPack.h"

SocketDelegate::SocketDelegate()
{
}

SocketDelegate::~SocketDelegate()
{
}

bool SocketDelegate::init()
{
    return true;
}

void SocketDelegate::onConnectTimeout()
{
    CCLOG("socket connect timeout!");
}

void SocketDelegate::onConnected()
{
    CCLOG("socked connectd!");
}

void SocketDelegate::onDisconnected()
{
    CCLOG("socked disconnected!");
}

void SocketDelegate::onError()
{
    CCLOG("socked error!");
}

void SocketDelegate::onMessage(char *pMsg)
{
    CCLOG("recv msg = %s", pMsg);

    Pack p1(pMsg);
    LC_LOGIN_REQ req2;
    CBuffer buf2(p1.getBuffer());
    buf2 >> req2;
}