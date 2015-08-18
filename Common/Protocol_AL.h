#ifndef _PROTOCOLAL_H_INCLUDED_
#define _PROTOCOLAL_H_INCLUDED_


/***** 代理服务器 -> 登陆服务器 *****/
/***** Agent -> Login *****/

enum eAL_Connect_Protocol {
	AL_Heartbeat_SYN 		= 1000,
	AL_Heartbeat_ANC,
};

enum eAL_ClientLogin_Protocol {
	AL_Prelogin_SYN, 				
	AL_Prelogin_ANC,
	AL_Relogin_SYN, 				
	AL_ReLogin_ANC,
	AL_Login_SYN,			
	AL_Login_ANC,				
	AL_Logout_SYN, 				
	AL_Logout_ANC, 				
};


#endif // _PROTOCOLAL_H_INCLUDED_
