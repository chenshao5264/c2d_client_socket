#include "MsgServiceInterface.h"
#include "ClientNet/MsgService/MsgPipe.h"

IMsgService::IMsgService()
{
    MsgPipe::getInstance()->registService(this);
}

IMsgService::~IMsgService()
{
    MsgPipe::getInstance()->unRegistService(this);
}
