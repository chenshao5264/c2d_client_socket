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
        �������Է���������Ϣ
    */
    virtual void process(Pack& pack) = 0;
};

#endif
