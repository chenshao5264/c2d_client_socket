#ifndef __Protocol_Struct_H__
#define __Protocol_Struct_H__

#include "ByteConverter.h"

#define NET_PACKET(T) struct T

#define NET_BUFFER_OUT(T) inline ByteConvert &operator<<(ByteConvert &buf, T&obj)
#define NET_BUFFER_IN(T)  inline ByteConvert &operator>>(ByteConvert &buf, T&obj)

NET_PACKET(Player)
{
    int age;
    std::string name;
    std::map<int, std::string> cards;
};

NET_BUFFER_OUT(Player)
{
    return buf << obj.age << obj.name;
}

NET_BUFFER_IN(Player)
{
    return buf >> obj.age >> obj.name;
}

#endif
