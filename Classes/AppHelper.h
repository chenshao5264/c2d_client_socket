#ifndef __AppHelper_H__
#define __AppHelper_H__

#include "Public/Singleton.h"

class AppHelper : public CSingleton<AppHelper>
{ 
    FRIEND_SINGLETON_CLASS(AppHelper);
private:
    AppHelper();
public:
    
    ~AppHelper();

    // app ��һ������
    void didLaunched();
    // app �ر�
    void didShuted();
};

#endif
