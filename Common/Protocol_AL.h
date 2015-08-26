#ifndef _PROTOCOLAL_H_INCLUDED_
#define _PROTOCOLAL_H_INCLUDED_


/***** 代理服务器 -> 登陆服务器 *****/
/***** Agent -> Login *****/

enum eAL_Connect_Protocol {
	AL_Heartbeat_SYN 		= 1000,
	AL_Heartbeat_ANC,
};

enum eAL_ClientLogin_Protocol {
	AL_PreLogin_REQ, 			// 预登陆 请求
	AL_PreLogin_ANC, 			// 预登陆 回应
	
	AL_Login_REQ, 				// 正式登陆 请求
	AL_Login_ANC, 				// 正式登陆 回应
	
	AL_ReLogin_REQ, 			// 再次登陆 请求
	AL_ReLogin_ANC, 			// 再次登陆 回应
		
	AL_Logout_REQ, 				// 登出 请求 				
	AL_Logout_ANC, 				// 登出 回应
	
	AL_SaveUserKey_SYN, 		// Login生成的UserKey发送给Agent保存(所有的SYN消息都不需要应答)
};


#endif // _PROTOCOLAL_H_INCLUDED_
