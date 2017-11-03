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
    // ����µ����Է���������Ϣ
    void appendOne(Pack& pack);
    void processOne();
    // ������Ϣ����
    void start();
    // �ݶ�������Ϣ
    void pause();
    bool isPause() const { return m_isPause; }
    // �ָ�������Ϣ
    void recover();
    
    const std::deque<Pack>& getMsgDeque() const { return m_msgDeque; }

    //@brief: ע����Ϣ�������
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
