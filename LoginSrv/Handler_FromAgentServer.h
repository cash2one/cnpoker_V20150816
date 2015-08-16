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

	HANDLER_DECL( AL_Prelogin_SYN );
	HANDLER_DECL( AL_Relogin_SYN );
	HANDLER_DECL( AL_Login_SYN );
	HANDLER_DECL( AL_Logout_SYN );
};


#endif