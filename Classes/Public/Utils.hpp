#ifndef __Utils_H__
#define __Utils_H__

#include "cocos2d.h"

#include <string>

class Utils
{
public:
    static std::string toString(int number)
    {
        return cocos2d::StringUtils::format("%d", number);
    }

    static std::string toString(std::string str)
    {
        return cocos2d::StringUtils::format("%s", str);
    }
};

#endif
