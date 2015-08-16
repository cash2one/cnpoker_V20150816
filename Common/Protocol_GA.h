#ifndef _PROTOCOLGA_H_INCLUDED_
#define _PROTOCOLGA_H_INCLUDED_

/***** 游戏服务器 -> 代理服务器 *****/
/***** Game -> Agent *****/

enum eGA_Connect_Protocol {
	GA_Heartbeat_SYN 		= 1000,
	GA_Heartbeat_ANC,
};

enum eGA_ClientLogin_Protocol {
	GA_Login_SYN, 				// 登入请求：【临时Key值，玩家ID】
	GA_Login_ANC, 				// 登入请求：【临时Key值，玩家游戏ID】
	GA_Logout_REQ, 				// 退出请求：【临时Key值】
	GA_Logout_ANC, 				// 退出请求：【临时Key值】
};

enum eGA_Game_Protocol {
	GA_StartGame_REQ 		= 2000,
	GA_StartGame_ANC,
	GA_JoinGame_REQ, 				// 加入房加：【玩家X】
	GA_JoinGame_ANC, 				// 加入房加：【房间ID, 玩家{1,2,3}】
	GA_InitCards_BRD, 				// 服务器给所有玩家发牌：【牌数、牌串】
	GA_Discards_BRD, 				// 出牌通知：【玩家ID、开始时间，结束时间】
	GA_Discards_SYN, 				// 玩家出牌：【牌数、牌值串】
	GA_Discards_ANC, 				// 出牌应答：0-不合格、1-合格
	GA_MaxCards_BRD, 				// 单圈胜利：0-不合格、1-合格
	GA_WinPlayer_BRD, 				// 单局胜利：0-不合格、1-合格
	GA_EndGame_SYN,
};

#endif // _PROTOCOLGA_H_INCLUDED_
