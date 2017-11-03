#ifndef __Msg_Pipe_H__
#define __Msg_Pipe_H__

#include <deque>
#include <set>

#include "cocos2d.h"
#include "Public/Singleton.h"

#include "ClientNet/NetPack.h"

class IMsgService;

class MsgPipe : public CSingleton<MsgPipe>
{
    FRIEND_SINGLETON_CLASS(MsgPipe);
private:
    MsgPipe();
public:
    ~MsgPipe();

public:
    // 添加新的来自服务器的消息
    void appendOne(Pack& pack);
    void processOne();
    // 启动消息处理
    void start();
    // 暂定处理消息
    void pause();
    bool isPause() const { return m_isPause; }
    // 恢复处理消息
    void recover();
    
    const std::deque<Pack>& getMsgDeque() const { return m_msgDeque; }

    //@brief: 注册消息处理服务
    void registService(IMsgService*);
    void unRegistService(IMsgService*);
private:

    class ScheduleRunner : public cocos2d::Ref
    {
    public:
        ScheduleRunner();
        ~ScheduleRunner();

        void update(float dt);
    };

private:
    bool m_isPause;
    std::deque<Pack> m_msgDeque;
    std::set<IMsgService*> m_setMsgService;

};

#endif
