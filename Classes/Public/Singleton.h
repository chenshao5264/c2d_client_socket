#ifndef __Singleton_H__
#define __Singleton_H__

#include "Uncopyable.h"

template<class T>
class CSingleton : public Uncopyable
{
public:
    static void pruge()
    {
        if (m_pInstance)
        {
            delete m_pInstance;
            m_pInstance = nullptr;
        }
    }

    static T* getInstance()
    {
        if (nullptr == m_pInstance)
        {
            // ¶þ´Î¼ì²é
            if (nullptr == m_pInstance)
            {
                m_pInstance = new (std::nothrow) T();
            }
        }
        return m_pInstance;
    }

protected:
    CSingleton() {}

    virtual ~CSingleton() {}
private:
    static T* m_pInstance;
};

template<class T>
T* CSingleton<T>::m_pInstance = nullptr;

#undef FRIEND_SINGLETON_CLASS
#define FRIEND_SINGLETON_CLASS(clsName) friend class CSingleton<clsName>

#endif
