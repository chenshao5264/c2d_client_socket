#ifndef __Byte_Convert_H__
#define __Byte_Convert_H__

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

class ByteConvert
{
    enum { buflen = MAX_SR_LEN };

public:
    ByteConvert()
    {
        this->reset();
    }

    ~ByteConvert()
    {

    }

private:
    void reset()
    {
        memset(m_szSendData, 0x00, sizeof(m_szSendData));
        m_pWriteData = m_szSendData;
        m_pReadData  = m_szSendData;
        m_len = 0;
        m_num = 0;
    }

    // 基础类型转为byte[]
    void write(void* body, size_t uLen)
    {
        if ((buflen - m_len) > static_cast<int>(uLen))
        {
            memcpy(m_pWriteData, body, uLen);
            m_pWriteData += uLen;
            m_len += uLen;
            ++m_num;
        }
    }

    // byte[]转为基础类型
    void read(void* pData, size_t nLen)
    {
        if (nLen > 0 && m_len - nLen >= 0)
        {
            memcpy(pData, m_pReadData, nLen);
            m_pReadData += nLen;
            m_len -= nLen;
        }
    }
    
public:
    // 基础类型 write & read
    // write
    template <class T>
    ByteConvert& operator<<(T &val)
    {
        this->write((void*)(&val), sizeof(val));
        return *this;
    }
    // read
    template <class T>
    ByteConvert& operator>>(T &val)
    {
        this->read((void*)(&val), sizeof(val));
        return *this;
    }

    // string write & read
    // write
    ByteConvert& operator<<(std::string &val)
    {
        size_t uLen = val.length();
        *this << uLen; // 先写入string的长度
        this->write((void*)(val.c_str()), uLen);
        return *this;
    }
    // read
    ByteConvert& operator>>(std::string &val)
    {
        size_t uLen = 0;
        *this >> uLen;
        val.assign(m_pReadData, uLen);

        size_t len1 = uLen * sizeof(char);
        m_pReadData += len1;
        m_len -= len1;
        return *this;
    }

    // array write & read
    // write
    template <class T>
    ByteConvert& operator<<(PackageArray<T> &val)
    {
        for (short i = 0; i < val.m_sLen; ++i)
        {
            *this << val.m_pT[i];
        }
        return *this;
    }

    // read
    template <class T>
    ByteConvert& operator >> (PackageArray<T> &val)
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
    ByteConvert& operator<<(std::vector<T> &val)
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
    ByteConvert& operator >> (std::vector<T> &val)
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
    ByteConvert& operator<<(std::list<T> &val)
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
    ByteConvert& operator >> (std::list<T> &val)
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
    ByteConvert& operator<<(std::deque<T> &val) 
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
    ByteConvert& operator >> (std::deque<T> &val)
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
    ByteConvert& operator << (std::map<_Kty, _ty> &val)
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
    ByteConvert& operator >> (std::map<_Kty, _ty> &val)
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
    ByteConvert& operator<<(std::set<T> &val)
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
    ByteConvert& operator >> (std::set<T> &val)
    {
        size_t uLen = 0;
        *this >> uLen;

        auto iter = val.begin();
        while (iter != val.end())
        {
            *this << (*iter++);
        }
        return *this;
    }

public:
    // 返回当前缓冲区的长度
    size_t getBufferLength()
    {
        return m_len;
    }

    // 返回缓冲区中的包体个数
    size_t getBufferCount()
    {
        return m_num;
    }

private:
    char		m_szSendData[buflen];			//一个装数据的BODY_BUF_LEN包长
    char*		m_pWriteData;					//指向当前写入数据的字符串的首位置
    int			m_len;							//当前长度
    int			m_num;							//包体个数
    char*		m_pReadData;					//指向当前获取数据的字符串的首位置
};

#endif
