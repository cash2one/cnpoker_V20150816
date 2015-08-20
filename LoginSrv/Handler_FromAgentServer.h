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

	HANDLER_DECL( AL_PreLogin_REQ );
	HANDLER_DECL( AL_Login_REQ );
	
	HANDLER_DECL( AL_ReLogin_REQ );
	
	HANDLER_DECL( AL_Logout_REQ );
};


#endif