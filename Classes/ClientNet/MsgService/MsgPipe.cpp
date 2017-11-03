#include "MsgPipe.h"
#include "Service.hpp"
#include "AppModel.h"

using namespace cocos2d;

MsgPipe::MsgPipe()
    : m_isPause(false)

{
    
}

MsgPipe::~MsgPipe()
{
    for (const auto& it : m_setMsgService)
    {
        if (it)
        {
            delete it;
        }
    }
}

void MsgPipe::appendOne(Pack & pack)
{
    m_msgDeque.push_back(pack);
}

void MsgPipe::start()
{
    new ScheduleRunner();
    m_isPause = false;
}

void MsgPipe::pause()
{
    m_isPause = true;
}

void MsgPipe::recover()
{
    m_isPause = false;
}

void MsgPipe::registService(IMsgService *service)
{
    if (service)
    {
        m_setMsgService.insert(service);
    }
}

void MsgPipe::unRegistService(IMsgService *service)
{
   auto iter =  m_setMsgService.find(service);
   if (iter != m_setMsgService.end())
   {
       m_setMsgService.erase(iter);
   }
}

void MsgPipe::processOne()
{
    if (this->isPause())
    {
        return;
    }

    if (m_msgDeque.size() == 0)
    {
        return;
    }

    Pack pack = m_msgDeque.at(0);
    m_msgDeque.pop_front();

    for (const auto& it : m_setMsgService)
    {
        if (it && it->process(pack))
        {
            break;
        }
    }
}

//
MsgPipe::ScheduleRunner::ScheduleRunner()
{
    Director::getInstance()->getScheduler()->scheduleUpdate(this, 1, false);
}

MsgPipe::ScheduleRunner::~ScheduleRunner()
{
    Director::getInstance()->getScheduler()->unscheduleUpdate(this);
}

void MsgPipe::ScheduleRunner::update(float dt)
{
    MsgPipe::getInstance()->processOne();
}


