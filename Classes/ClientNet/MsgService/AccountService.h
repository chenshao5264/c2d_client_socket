#ifndef __AccountService_H__
#define __AccountService_H__

#include "MsgServiceInterface.h"



class AccountService : public IMsgService
{
public:
    AccountService();
    virtual ~AccountService();

    virtual bool process(Pack& pack);
};

#endif
