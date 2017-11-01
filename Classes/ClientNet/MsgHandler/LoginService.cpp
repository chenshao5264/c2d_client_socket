#include "LoginService.h"

LoginService::LoginService()
{
}

LoginService::~LoginService()
{
}

void LoginService::process(Pack& pack)
{
    switch (pack.getMethod())
    {
    case LC_LOGIN_REQ_P :
    {
        CBuffer buf(pack.getBuffer());
        LC_LOGIN_REQ req;
        buf >> req;
        break;
    }
    default:
        break;
    }
}
