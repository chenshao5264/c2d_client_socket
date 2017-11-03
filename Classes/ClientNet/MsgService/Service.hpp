#ifndef __ServiceFactory_H__
#define __ServiceFactory_H__

#include "AccountService.h"

class Service
{
public:
    static void createServices()
    {
        // 实例化消息处理服务
        NEW_SERVICE(AccountService);
    }
};

#endif
