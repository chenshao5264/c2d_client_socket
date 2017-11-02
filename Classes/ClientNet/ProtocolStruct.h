#ifndef __Protocol_Struct_H__
#define __Protocol_Struct_H__

#include "ByteBuffer.h"

#define NET_PACKET(T) struct T

#define NET_BUFFER_OUT(T) inline CBuffer &operator<<(CBuffer &buf, T &obj)
#define NET_BUFFER_IN(T)  inline CBuffer &operator>>(CBuffer &buf, T &obj)

NET_PACKET(PACKET_DEMO)
{
    char day;
    int age;
    std::string name;
    std::map<int, std::string> mapCards;
    std::vector<std::string> vecCards;
    std::list<std::string> listCards;
    std::deque<std::string> dequeCards;
    std::set<std::string> setCards;
    PACKET_DEMO()
        : day(0)
        , age(0)
    {

    }
};

NET_BUFFER_OUT(PACKET_DEMO)
{
    return buf << obj.day << obj.age << obj.name << obj.mapCards << obj.vecCards << obj.listCards << obj.dequeCards << obj.setCards;
}

NET_BUFFER_IN(PACKET_DEMO)
{
    return buf >> obj.day >> obj.age >> obj.name >> obj.mapCards >> obj.vecCards >> obj.listCards >> obj.dequeCards >> obj.setCards;
}

NET_PACKET(LC_LOGIN_REQ)
{
    int time;
    std::string strAccount;
    std::string strPwd;
};

NET_BUFFER_OUT(LC_LOGIN_REQ)
{
    return buf << obj.time << obj.strAccount << obj.strPwd;
}

NET_BUFFER_IN(LC_LOGIN_REQ)
{
    return buf >> obj.time >> obj.strAccount >> obj.strPwd;
}

#endif
