#ifndef _PROTOCOLCA_H_INCLUDED_
#define _PROTOCOLCA_H_INCLUDED_

#include "Protocol.h"
/***** 客户端 -> 代理服务器 *****/
/***** Client -> Agent *****/

enum eCA_Connect_Protocol {
	CA_ServerType_SYN 		= 101,
	CA_Heartbeat_SYN,
};

enum eCA_ClientLogin_Protocol {
	CA_PreLogin_REQ 		= 201,	// 登入请求：【临时Key值】
	CA_PreLogin_ANC,				// 登入应答：【临时Key值】
	CA_PreLogin_NAK,
	
	CA_Login_REQ,					// 登入请求：【临时Key值】
	CA_Login_ANC, 					// 登入应答：【临时Key值】
	CA_Login_NAK,
	
	CA_ReLogin_REQ, 				// 登入转入或转出请求: 【临时Key值】
	CA_ReLogin_ANC, 				// 登入转入或转出请求: 【临时Key值】
	
	CA_Logout_REQ, 					// 退出请求：【临时Key值】
	CA_Logout_ANC, 					// 退出请求：【临时Key值】
};

enum eCA_Game_Protocol {
	CA_StartGame_REQ 		= 301,
	CA_StartGame_ANC,
	
	CA_JoinRoom_REQ, 				// 加入房间：【玩家X】
	CA_JoinRoom_ANC, 				// 加入房间：【房间ID】
	
	CA_JoinTable_REQ, 				// 加入桌子：【玩家X】
	CA_JoinTable_ANC, 				// 加入桌子：【房间ID, 玩家{1,2,3}】
	
	CA_InitCards_BRD, 				// 服务器给所有玩家发牌：【牌数、牌串】
	
	CA_ContendWithBanker_REQ,  		// 争夺庄家：【玩家ID】
	
	CA_InitBanker_BRD, 				// 初始庄家：【玩家ID】
	
	CA_ShowCards_REQ, 				// 明牌请求：【玩家ID】
	CA_ShowCards_BRD, 				// 明牌请求：【玩家ID、牌数、牌串】
		
	CA_Discards_BRD, 				// 出牌通知：【玩家ID、开始时间，结束时间】	
	CA_Discards_REQ, 				// 玩家出牌：【牌数、牌值串】
	CA_Discards_ANC, 				// 出牌应答：0-不合格、1-合格
	
	CA_MaxCards_BRD, 				// 单圈胜利：0-不合格、1-合格
	CA_WinPlayer_BRD, 				// 单局胜利：0-不合格、1-合格
	CA_EndGame_SYN
};

#endif // _PROTOCOLCA_H_INCLUDED_
