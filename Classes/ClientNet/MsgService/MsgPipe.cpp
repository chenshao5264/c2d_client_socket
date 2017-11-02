#include "MsgPipe.h"

#include "LoginService.h"

using namespace cocos2d;

MsgPipe::MsgPipe()
    : m_isPause(false)

{
    m_pLoginService = new LoginService();
}

MsgPipe::~MsgPipe()
{
    
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

const std::deque<Pack>& MsgPipe::getMsgDeque() const
{
    return m_msgDeque;
}

bool MsgPipe::isPause() const
{
    return m_isPause;
}

void MsgPipe::process(Pack & pack)
{
    if (pack.getMethod() == PACKET_DEMO_P)
    {
        CBuffer buf(pack.getBuffer());
        PACKET_DEMO req;
        return;
    }

    int method = pack.getMethod();
    if (method >= PROTOCOL_LC_START && method < PROTOCOL_LC_END)
    {
        m_pLoginService->process(pack);
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
    if (MsgPipe::getInstance()->isPause())
    {
        return;
    }

    auto msgDeque = MsgPipe::getInstance()->getMsgDeque();
    if (msgDeque.size() == 0)
    {
        return;
    }

    Pack pack = msgDeque.at(0);
    msgDeque.pop_front();
    MsgPipe::getInstance()->process(pack);
}


