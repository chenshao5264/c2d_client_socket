#include "SocketDelegate.h"

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

void SocketDelegate::onMessage(char * pData)
{
    CCLOG("recv data = %s", pData);
}