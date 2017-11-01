#ifndef __MsgServiceInterface_H__
#define __MsgServiceInterface_H__

#include "ClientNet/NetPack.h"

class IMsgService
{
public:
    IMsgService() {};
    virtual ~IMsgService() {};
public:
    virtual void process(Pack& pack) = 0;
};

#endif
