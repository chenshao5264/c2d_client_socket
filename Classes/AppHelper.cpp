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
    // ���������������Ϣ�ķ���
    Service::createServices();
}
