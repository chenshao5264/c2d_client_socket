#ifndef __Protocol_Struct_H__
#define __Protocol_Struct_H__

#include "ByteBuffer.h"

#define NET_PACKET(T) struct T

#define NET_BUFFER_OUT(T) inline CBuffer &operator<<(CBuffer &buf, T &obj)
#define NET_BUFFER_IN(T)  inline CBuffer &operator>>(CBuffer &buf, T &obj)

NET_PACKET(Player)
{
    char day;
    int age;
    std::string name;
    std::map<int, std::string> mapCards;
    std::vector<std::string> vecCards;
    std::list<std::string> listCards;
    std::deque<std::string> dequeCards;
    std::set<std::string> setCards;
};

NET_BUFFER_OUT(Player)
{
    return buf << obj.day << obj.age << obj.name << obj.mapCards << obj.vecCards << obj.listCards << obj.dequeCards << obj.setCards;
}

NET_BUFFER_IN(Player)
{
    return buf >> obj.day >> obj.age >> obj.name >> obj.mapCards >> obj.vecCards >> obj.listCards >> obj.dequeCards >> obj.setCards;
}

#endif
