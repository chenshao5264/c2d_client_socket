#ifndef __Protocol_H__
#define __Protocol_H__


#define PROTOCOL_LC_START 1000
#define PROTOCOL_LC_END   2000

enum Protocol
{
    PACKET_DEMO_P  = 1999,                // ����Э��
    INVALID_P      = 0,                       // ��ЧЭ�� 
    LOGIN_START_P  = PROTOCOL_LC_START,       // ��¼Э�鿪ʼ
    LC_LOGIN_REQ_P,                           // ��¼����


};

#endif
