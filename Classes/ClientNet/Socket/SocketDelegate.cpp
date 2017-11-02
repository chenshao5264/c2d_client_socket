#include "SocketDelegate.h"

#include "ClientNet/NetPack.h"
#include "ClientNet/MsgService/MsgPipe.h"

SocketDelegate::SocketDelegate()
{
}

SocketDelegate::~SocketDelegate()
{

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
    Pack pack(pMsg);

    int method = pack.getMethod();
    if (method == 0)
    {
        CCLOG("Invalid protocol!");
        return;
    }

    CCLOG("proc msg method = %d", method);

    MsgPipe::getInstance()->appendOne(pack);
}