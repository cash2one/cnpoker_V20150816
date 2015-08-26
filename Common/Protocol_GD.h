#ifndef _PROTOCOLGD_H_INCLUDED_
#define _PROTOCOLGD_H_INCLUDED_

/***** 游戏服务器 -> 数据库 *****/
/***** Game -> DBServer *****/

enum eGD_Connect_Protocol {				
	GD_Heartbeat_SYN,					
	GD_Heartbeat_ANC,
};

enum eGD_ClientLogin_Protocol {
	GD_Login_REQ, 				// 登入请求：【玩家ID】
	GD_Login_ANC, 				// 登入请求：【玩家数据包】
	GD_Login_NAK,
	
	GD_Logout_REQ, 				// 登入请求：【玩家ID】
	GD_Logout_ANC, 				// 清除缓存
};

enum eGD_Update_Protocol { 		// GameServer每10分钟更新一次数据到数据库
	GD_Save_CMD, 				// 更新通知
	GD_Save_ANC, 				// 返回更新
	GD_Update_CMD, 				// 更新通知
	GD_Update_ANC, 				// 返回更新
};

#endif // _PROTOCOLGD_H_INCLUDED_
