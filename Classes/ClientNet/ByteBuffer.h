#ifndef __Byte_Buffer_H__
#define __Byte_Buffer_H__

#include <cstring>

#include <vector>
#include <list>
#include <deque>
#include <map>
#include <set>

const int        MAX_SR_LEN = (1024 * 8 - 40);


template<class T>
class PackageArray
{
public:
    //pT is the address of array, sLen is length of address
    PackageArray(T *pT, short sLen)
    {
        m_pT = pT;
        m_sLen = sLen;
    }

public:
    T *m_pT;
    short m_sLen;
};

class CBuffer
{
    enum { buflen = MAX_SR_LEN };

public:
    CBuffer()
    {
        this->reset();
    }

    ~CBuffer()
    {

    }
    //拷贝构造函数
    CBuffer(const CBuffer& res)
    {
        this->reset();
        this->write((void*)(res.m_pData), res.m_iLen);
    }
    //赋值函数
    const CBuffer& operator=(const CBuffer& res)
    {
        this->reset();
        this->write((void*)(res.m_pData), res.m_iLen);
        return *this;
    }

private:
    void reset()
    {
        memset(m_pData, 0, sizeof(m_pData));
        m_pWriteData = m_pData;
        m_pReadData  = m_pData;
        m_iLen = 0;
    }

    // 基础类型转为byte[]
    void write(void* body, int iLen)
    {
        if (buflen - m_iLen > iLen)
        {
            memcpy(m_pWriteData, body, iLen);
            m_pWriteData += iLen; // 指针地址偏移, 数据可以通过m_pData获取到
            m_iLen += iLen;
        }
    }

    // byte[]转为基础类型
    void read(void* pData, int iLen)
    {
        if (iLen > 0 && (m_iLen - iLen) >= 0)
        {
            memcpy(pData, m_pReadData, iLen);
            m_pReadData += iLen; // 指针地址偏移, 数据可以通过m_pData获取到
            m_iLen -= iLen;
        }
    }
public:
    void writeToBuf(void* body, int iLen)
    {
        this->write(body, iLen);
    }

    // 基础类型 write & read
    // write
    template <class T>
    CBuffer& operator<<(T &val)
    {
        this->write((void*)(&val), sizeof(val));
        return *this;
    }
    // read
    template <class T>
    CBuffer& operator>>(T &val)
    {
        this->read((void*)(&val), sizeof(val));
        return *this;
    }

    // string write & read
    // write
    CBuffer& operator<<(std::string &val)
    {
        size_t uLen = val.length();
        *this << uLen; // 先写入string的长度
        this->write((void*)(val.c_str()), uLen);
        return *this;
    }
    CBuffer& operator<<(const std::string &val)
    {
        *this << const_cast<std::string&>(val);
        return *this;
    }
    // read
    CBuffer& operator>>(std::string &val)
    {
        size_t uLen = 0;
        *this >> uLen;
        val.assign(m_pReadData, uLen);

        size_t len1 = uLen * sizeof(char);
        m_pReadData += len1;
        m_iLen -= len1;
        return *this;
    }

    // array write & read
    // write
    template <class T>
    CBuffer& operator<<(PackageArray<T> &val)
    {
        for (short i = 0; i < val.m_sLen; ++i)
        {
            *this << val.m_pT[i];
        }
        return *this;
    }

    // read
    template <class T>
    CBuffer& operator >> (PackageArray<T> &val)
    {
        for (short i = 0; i < val.m_sLen; i++)
        {
            *this >> val.m_pT[i];
        }
        return *this;
    }

    // vector write & read
    // write
    template <class T>
    CBuffer& operator<<(std::vector<T> &val)
    {
        size_t uLen = val.size();
        *this << uLen;
        for (size_t i = 0; i < uLen; ++i)
        {
            *this << val[i];
        }
        return *this;
    }
    // read
    template <class T>
    CBuffer& operator >> (std::vector<T> &val)
    {
        size_t uLen = 0;
        *this >> uLen;
        for (size_t i = 0; i < uLen; ++i)
        {
            T t;
            *this >> t;
            val.push_back(t);
        }
        return *this;
    }

    // list write & read
    // write
    template <class T>
    CBuffer& operator<<(std::list<T> &val)
    {
        size_t uLen = val.size();
        *this << uLen;
        auto iter = val.begin();
        
        while (iter != val.end())
        {
            *this << (*iter++);
        }
        return *this;
    }
    // read
    template <class T>
    CBuffer& operator >> (std::list<T> &val)
    {
        size_t uLen = 0;
        *this >> uLen;
        for (size_t i = 0; i < uLen; ++i)
        {
            T t;
            *this >> t;
            val.push_back(t);
        }
        return *this;
    }

    // deque write & read
    // write
    template <class T>
    CBuffer& operator<<(std::deque<T> &val) 
    {
        size_t uLen = val.size();
        *this << uLen;

        auto iter = val.begin();
        while (iter != val.end())
        {
            *this << (*iter++);
        }
        return *this;
    }
    // read
    template <class T>
    CBuffer& operator >> (std::deque<T> &val)
    {
        size_t uLen = 0;
        *this >> uLen;
        for (size_t i = 0; i < uLen; ++i)
        {
            T t;
            *this >> t;
            val.push_back(t);
        }
        return *this;
    }

    // map write & read
    // write
    template <class _Kty, class _ty>
    CBuffer& operator << (std::map<_Kty, _ty> &val)
    {
        size_t uLen = val.size();
        *this << uLen;

        auto iter = val.begin();
        while (iter != val.end())
        {
            *this << iter->first;
            *this << iter->second;
            ++iter;
        }
        return *this;
    }
    // read
    template <class _Kty, class _ty>
    CBuffer& operator >> (std::map<_Kty, _ty> &val)
    {
        size_t uLen = 0;
        *this >> uLen;

        for (size_t i = 0; i < uLen; ++i)
        {
            _Kty fdata;
            *this >> fdata;

            _ty sdata;
            *this >> sdata;
            val.insert(std::make_pair(fdata, sdata));
        }
        return *this;
    }

    // set write & read
    // write
    template <class T>
    CBuffer& operator<<(std::set<T> &val)
    {
        size_t uLen = val.size();
        *this << uLen;

        auto iter = val.begin();
        while (iter != val.end())
        {
            *this << (*iter++);
        }
        return *this;
    }
    // read
    template <class T>
    CBuffer& operator >> (std::set<T> &val)
    {
        size_t uLen = 0;
        *this >> uLen;

        for (size_t i = 0; i < uLen; ++i)
        {
            T t;
            *this >> t;
            val.insert(t);
        }
        return *this;
    }

public:
    char* getData()
    {
        return m_pData;
    }
    // 返回当前缓冲区的长度
    size_t getLength()
    {
        return m_iLen;
    }

private:
    char		m_pData[buflen];			// 一个装数据的BODY_BUF_LEN包长
    char*		m_pWriteData;				// 指向当前写入数据的字符串的首位置
    char*		m_pReadData;				// 指向当前获取数据的字符串的首位置
    int			m_iLen;						// 当前长度
    
};

#endif
