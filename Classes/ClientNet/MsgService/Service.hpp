#ifndef __ServiceFactory_H__
#define __ServiceFactory_H__

#include "AccountService.h"

class Service
{
public:
    static void createServices()
    {
        // ʵ������Ϣ�������
        NEW_SERVICE(AccountService);
    }
};

#endif
