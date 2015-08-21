#ifndef _HANDLER_FROMGAMESERVER_H_INCLUDED_
#define _HANDLER_FROMGAMESERVER_H_INCLUDED_

#include <Common.h>

#include "ServerSession.h"

#define HANDLER_DECL( p )			static VOID On##p( ServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize )
#define HANDLER_IMPL( p )			VOID Handler_FromGameServer::On##p( ServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize )

class Handler_FromGameServer
{
public:
	Handler_FromGameServer(void);
	~Handler_FromGameServer(void);

	HANDLER_DECL( AG_Login_ANC);
	
	HANDLER_DECL( AG_Logout_ANC);
	
	HANDLER_DECL( AG_StartGame_ANC );
#if 0	
	HANDLER_DECL( AG_Heartbeat_SYN );
	
	HANDLER_DECL( AG_Relogin_SYN );
	
	
	HANDLER_DECL( AG_StartGame_REQ );
	HANDLER_DECL( AG_JoinRoom_REQ );
	HANDLER_DECL( AG_JoinTable_REQ );
	HANDLER_DECL( AG_ShowCards_REQ );
	HANDLER_DECL( AG_Discards_REQ );
	HANDLER_DECL( AG_EndGame_REQ );
#endif
};


#endif
