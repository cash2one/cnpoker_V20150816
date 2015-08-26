#ifndef _HANDLER_FROMAGENTSERVER_H_INCLUDED_
#define _HANDLER_FROMAGENTSERVER_H_INCLUDED_

#include <Common.h>

#include "ServerSession.h"

#define HANDLER_DECL( p )			static VOID On##p( ServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize )
#define HANDLER_IMPL( p )			VOID Handler_FromAgentServer::On##p( ServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize )

class Handler_FromAgentServer
{
public:
	Handler_FromAgentServer(void);
	~Handler_FromAgentServer(void);
	
#if 0
	HANDLER_DECL( AG_Heartbeat_SYN );
	
	HANDLER_DECL( AG_Logout_REQ );
	HANDLER_DECL( AG_Relogin_SYN );	
#endif
	HANDLER_DECL( AG_Login_REQ ); 	// 登录
	HANDLER_DECL( AG_Logout_REQ ); 	// 登出

	HANDLER_DECL( AG_StartGame_REQ ); // 开始游戏
	
	HANDLER_DECL( AG_JoinRoom_REQ );
	HANDLER_DECL( AG_JoinTable_REQ );
		
	HANDLER_DECL( AG_InitCards_BRD ); // 初始化牌
	
	HANDLER_DECL( AG_CallLandlord_REQ ); // 叫地主
	HANDLER_DECL( AG_GrabLandlord_REQ ); // 抢地主
	HANDLER_DECL( AG_GrabLandlord_BRD ); // 抢地主 广播
	
	HANDLER_DECL( AG_ShowCards_REQ );
	HANDLER_DECL( AG_Discards_REQ );
	
	HANDLER_DECL( AG_Pass_REQ ); // 要不起
	
	HANDLER_DECL( AG_EndGame_SYN );
	
	
};


#endif
