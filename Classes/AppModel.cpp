#include "AppModel.h"
#include "Public/Utils.hpp"
#include "Defines/Define.h"

using namespace cocos2d;

AppModel::AppModel()
{
}

AppModel::~AppModel()
{
}


void AppModel::doDemoMsg(const PACKET_DEMO & req)
{
    EventCustom customEvent(Utils::toString(e_do_demo_after));
    customEvent.setUserData((void*)(&req));
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&customEvent);
}

void AppModel::doLoginMsg(const LC_LOGIN_REQ& req)
{

    
}
