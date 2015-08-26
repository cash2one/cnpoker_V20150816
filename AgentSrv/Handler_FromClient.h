#ifndef _HANDLER_FROMCLIENT_H_INCLUDED_
#define _HANDLER_FROMCLIENT_H_INCLUDED_

#include <Common.h>
#include <Network.h>

#include "UserSession.h"

#define HANDLER_DECL( p )			static VOID On##p( UserSession * pUserSession, MSG_BASE * pMsg, WORD wSize )
#define HANDLER_IMPL( p )			VOID Handler_FromClient::On##p( UserSession * pUserSession, MSG_BASE * pMsg, WORD wSize )

class Handler_FromClient
{
public:
	Handler_FromClient(void);
	~Handler_FromClient(void);

	HANDLER_DECL( CA_Heartbeat_SYN );
	
	HANDLER_DECL( CA_PreLogin_REQ );
	
	HANDLER_DECL( CA_Login_REQ ); // 正式登陆
	
	HANDLER_DECL( CA_ReLogin_REQ ); // 重新登录
	
	HANDLER_DECL( CA_Logout_REQ); // 登出
	
	//
	HANDLER_DECL( CA_StartGame_REQ );
	
	// sylar 2015-08-16
	HANDLER_DECL( CA_JoinRoom_REQ );
	
	HANDLER_DECL( CA_JoinTable_REQ );
	HANDLER_DECL( CA_ShowCards_REQ );
	HANDLER_DECL( CA_Discards_BRD );
	HANDLER_DECL( CA_EndGame_SYN );
	
	HANDLER_DECL( CA_InitCards_BRD );
	//
};


#endif
