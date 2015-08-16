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

	HANDLER_DECL( GA_StartGame_REQ );
#if 0	
	HANDLER_DECL( GA_Heartbeat_SYN );
	
	HANDLER_DECL( GA_Logout_REQ);
	HANDLER_DECL( GA_Relogin_SYN );
	HANDLER_DECL( GA_Logout_REQ);
	
	HANDLER_DECL( GA_StartGame_REQ );
	HANDLER_DECL( GA_JoinRoom_REQ );
	HANDLER_DECL( GA_JoinTable_REQ );
	HANDLER_DECL( GA_ShowCards_REQ );
	HANDLER_DECL( GA_Discards_REQ );
	HANDLER_DECL( GA_EndGame_REQ );
#endif
};


#endif
