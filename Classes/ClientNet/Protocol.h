#ifndef __Protocol_H__
#define __Protocol_H__


#define PROTOCOL_LC_START 1000
#define PROTOCOL_LC_END   2000

enum Protocol
{
    PACKET_DEMO_P  = 1999,                // 测试协议
    INVALID_P      = 0,                       // 无效协议 
    LOGIN_START_P  = PROTOCOL_LC_START,       // 登录协议开始
    LC_LOGIN_REQ_P,                           // 登录请求


};

#endif
