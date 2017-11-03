#ifndef __MsgServiceInterface_H__
#define __MsgServiceInterface_H__

#include "ClientNet/NetPack.h"

#undef NEW_SERVICE
#define NEW_SERVICE(clsName) new (std::nothrow) clsName();


class IMsgService
{
public:
    IMsgService();
    virtual ~IMsgService();

public:
    /*
        �������Է���������Ϣ
    */
    virtual bool process(Pack& pack) = 0;
}; 

#endif
