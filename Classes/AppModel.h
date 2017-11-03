#ifndef __AppModel_H__
#define __AppModel_H__

#include "cocos2d.h"

#include "Public/Singleton.h"

#include "ClientNet/ProtocolStruct.h"



class AppModel : public CSingleton<AppModel>
{
    FRIEND_SINGLETON_CLASS(AppModel);
private:
    AppModel();
public:
    ~AppModel();

public:
    void doDemoMsg(const PACKET_DEMO& req);
    // 处理登录消息
    void doLoginMsg(const LC_LOGIN_REQ& req);
};

#endif
