#ifndef _PROTOCOLLD_H_INCLUDED_
#define _PROTOCOLLD_H_INCLUDED_

/***** 登陆服务器 -> 数据库 *****/
/***** Login -> DBServer *****/

enum eLD_Connect_Protocol {				
	LD_Heartbeat_SYN, 				//
	LD_Heartbeat_ANC, 				// 
};

enum eLD_ClientLogin_Protocol {
	LD_Login_REQ, 					// 登入请求：【玩家ID】
	LD_Login_ANC, 					// 认证确认
	
	LD_Logout_REQ, 					// 登入请求：【玩家ID】
	LD_Logout_ANC, 					// 清除缓存
};


#endif // _PROTOCOLLD_H_INCLUDED_
