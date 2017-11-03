#include "AccountService.h"

#include "cocos2d.h"
#include "MsgPipe.h"

#include "AppModel.h"

AccountService::AccountService()
{
    
}

AccountService::~AccountService()
{
    
}

bool AccountService::process(Pack& pack)
{   
    int method = pack.getMethod();
    if (method < PROTOCOL_LC_START || method >= PROTOCOL_LC_END)
    {
        return false;
    }

    switch (method)
    {
    case PACKET_DEMO_P :
    {
        CBuffer buf(pack.getBuffer());
        PACKET_DEMO req;
        buf >> req;
        AppModel::getInstance()->doDemoMsg(req);
    }
    case LC_LOGIN_REQ_P :
    {
        CBuffer buf(pack.getBuffer());
        LC_LOGIN_REQ req;
        buf >> req;
        AppModel::getInstance()->doLoginMsg(req);
        break;
    }

    default:
        CCLOG("no register AccountService protocol id = %d", method);
        break;
    }

    return true;
}
