#include "AppHelper.h"
#include "ClientNet/MsgService/Service.hpp"

AppHelper::AppHelper()
{

}

AppHelper::~AppHelper()
{

}

void AppHelper::didLaunched()
{
    // 创建处理服务器消息的服务
    Service::createServices();
}
