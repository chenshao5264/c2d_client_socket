#ifndef __MsgServiceInterface_H__
#define __MsgServiceInterface_H__

#include "ClientNet/NetPack.h"

class IMsgService
{
public:
    IMsgService() {};
    virtual ~IMsgService() {};
public:
    /*
        处理来自服务器的消息
    */
    virtual void process(Pack& pack) = 0;
};

#endif
