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

    // app 第一次启动
    void didLaunched();
    // app 关闭
    void didShuted();
};

#endif
