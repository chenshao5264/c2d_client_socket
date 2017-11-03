#ifndef __EventDispatcherEx_H__
#define __EventDispatcherEx_H__

#include <map>
#include <set>

#include "cocos2d.h"

#include "Public/Utils.hpp"
#include "Public/Singleton.h"
#include "Defines/Define.h"

NS_CC_BEGIN

class EventDispatcherEx : public CSingleton<EventDispatcherEx>
{
    FRIEND_SINGLETON_CLASS(EventDispatcherEx);
private:
    EventDispatcherEx() {};
public:
    EventListenerCustom* addCustomEventListener(Node* target, EvtName evtName, const std::function<void(EventCustom*)>& callback)
    {
        void* pTarget = static_cast<void*>(target);
        std::set<EvtName> setEvtNames;

        auto iter = m_addrMap.find(pTarget);
        if (iter != m_addrMap.end())
        {
   
            iter->second.insert(evtName);
        }
        {
            std::set<EvtName> setEvtNames;
            setEvtNames.insert(evtName);
            m_addrMap.insert(std::make_pair(pTarget, setEvtNames));
        }

        std::string strEventName = Utils::toString(evtName);
        Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(strEventName);
        return Director::getInstance()->getEventDispatcher()->addCustomEventListener(strEventName, callback);
    }

    void removeEventListenerForTarget(Node* target)
    {
        auto iter = m_addrMap.find(static_cast<void*>(target));
        
        if (iter == m_addrMap.end())
        {
            return;
        }

        auto setEvtNames = iter->second;

        for (const auto& evtName : setEvtNames)
        {
            Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(Utils::toString(evtName));
        }
    }

private:
    std::map<void*, std::set<EvtName>> m_addrMap;
};

NS_CC_END

#endif
