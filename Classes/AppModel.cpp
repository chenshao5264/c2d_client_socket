#include "AppModel.h"

using namespace cocos2d;

AppModel::AppModel()
{
}

AppModel::~AppModel()
{
}


void AppModel::doDemoMsg(const PACKET_DEMO & req)
{
    EventCustom customEndEvent("do_demo_after");
    customEndEvent.setUserData((void*)(&req));
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&customEndEvent);
}

void AppModel::doLoginMsg(const LC_LOGIN_REQ& req)
{

    
}
