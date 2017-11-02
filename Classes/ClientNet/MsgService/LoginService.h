#ifndef __LoginService_H__
#define __LoginService_H__

#include "MsgServiceInterface.h"

class LoginService : public IMsgService
{
public:
    LoginService();
    virtual ~LoginService();

    virtual void process(Pack& pack);
};

#endif
