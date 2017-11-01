#ifndef __Net_Pack_H__
#define __Net_Pack_H__

#include "DefinePublic.h"
#include "ByteBuffer.h"
#include "Protocol.h"
#include "ProtocolStruct.h"

struct PackHead
{
    User_ID iUId;
    int opCode;
    size_t bodyLength;

    PackHead()
        : iUId(0)
        , opCode(0)
        , bodyLength(0)
    {

    }
};

typedef char* PackBody;

const size_t PACK_HEAD_LEN = sizeof(PackHead);

const int MAX_PACK_LEN = (1024 * 8);

class Pack
{
    enum {
        buflen = MAX_PACK_LEN
    };

public:
    Pack()
    {
        this->reset();
    }

    // ָ�������ַ�����Ϊ�����Ĺ��캯��
    // ��Ҫ���ڽ��շ��������ֽ����������Pack
    Pack(char* pMsg)
    {
        this->reset();

        if (pMsg != NULL)
        {
            m_packHead = *(PackHead*)pMsg;
            if (m_packHead.bodyLength > 0 && m_packHead.bodyLength < MAX_PACK_LEN)
            {
                m_bodyBuf.writeToBuf(pMsg + PACK_HEAD_LEN, m_packHead.bodyLength);
            } 
            else
            {
                m_packHead.bodyLength = 0;
                m_packHead.iUId       = 0;
                m_packHead.opCode     = 0;
            }
        }
    }

    Pack(int method)
    {
        this->reset();

        m_packHead.opCode = method;
    }

    Pack(int method, char* pBody, size_t uLen)
    {
        this->reset();

        this->setMethod(method);
        this->setBody(pBody, uLen);
    }
    
    ~Pack()
    {

    }
private:
    void reset()
    {
        memset(&m_packHead, 0, PACK_HEAD_LEN);
        memset(m_pMsg, 0, sizeof(m_pMsg));
        m_iBodyLen = 0;
    }

public:
    // ƴ��head��body�����ݣ��������紫��
    char* getData()
    {
        int idx = 0;
        m_packHead.bodyLength = m_iBodyLen;
        memcpy(&m_pMsg[idx], &m_packHead, PACK_HEAD_LEN);
        idx += PACK_HEAD_LEN;
        memcpy(&m_pMsg[idx], m_bodyBuf.getData(), m_iBodyLen);
             
        return m_pMsg;
    }

    // ��ȡ�ܳ��� 
    size_t getLenght()
    {
        return PACK_HEAD_LEN + m_iBodyLen;
    }

    // ��ȡ������
    int getMethod()
    {
        return m_packHead.opCode;
    }

    void setMethod(int method)
    {
        m_packHead.opCode = method;
    }

    void setBody(char* pBody, int len)
    {
        m_bodyBuf.writeToBuf(pBody, len);
        m_iBodyLen = len;
    }

    CBuffer getBuffer()
    {
        return m_bodyBuf;
    }

private:
    char		m_pMsg[buflen];
    int         m_iBodyLen;
    PackHead    m_packHead;
    CBuffer     m_bodyBuf;
};

#endif
