#ifndef _PROTOCOLAG_H_INCLUDED_
#define _PROTOCOLAG_H_INCLUDED_

/***** 代理服务器 -> 游戏服务器 *****/
/***** Agent -> Game *****/

enum eAG_Connect_Protocol {
	AG_Heartbeat_SYN 		= 1000,
};

enum eAG_Game_Protocol {
	AG_StartGame_REQ 		= 101,
	AG_JoinGame_REQ,
};


#endif // _PROTOCOLAG_H_INCLUDED_