#ifndef __Msg_Pipe_H__
#define __Msg_Pipe_H__

#include <deque>

#include "cocos2d.h"
#include "Public/Singleton.h"

#include "ClientNet/NetPack.h"

class IMsgService;
//class LoginService;
class MsgPipe : public CSingleton<MsgPipe>
{
public:
    MsgPipe();
    ~MsgPipe();

public:
    // 添加新的来自服务器的消息
    void appendOne(Pack& pack);

    // 启动消息处理
    void start();
    // 暂定
    void pause();
    // 恢复
    void recover();
    
    const std::deque<Pack>& getMsgDeque() const;
    bool isPause() const;
private:
    void process(Pack& pack);

    class ScheduleRunner : public cocos2d::Ref
    {
    public:
        ScheduleRunner();
        ~ScheduleRunner();

        void update(float dt);
    };

private:
    std::deque<Pack> m_msgDeque;

    bool m_isPause;

    IMsgService* m_pLoginService;
};

#endif
