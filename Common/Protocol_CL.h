#ifndef _PROTOCOLCL_H_INCLUDED_
#define _PROTOCOLCL_H_INCLUDED_

/***** 客户端 -> 登陆服务器 *****/
/***** Client -> Login *****/

enum eCL_Connect_Protocol {
	CL_Heartbeat_SYN		= 1000,
	CL_Heartbeat_ANC,
	CL_Login_REQ, 						// 登入请求：【用户名，MD5(日期+密码)】
	CL_Login_ANC, 						// 登入应答：【 临时Key值，指定Agent服务器{IP, Port}】
	CL_Logout_REQ, 						// 退出请求：【临时Key值】
	CL_Logout_ANC, 						// 退出应答：【结果{0，1}】
};

#endif // _PROTOCOLCL_H_INCLUDED_
