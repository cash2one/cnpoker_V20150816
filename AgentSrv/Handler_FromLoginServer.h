#ifndef _HANDLER_FROMLOGINSERVER_H_INCLUDED_
#define _HANDLER_FROMLOGINSERVER_H_INCLUDED_

#include <Common.h>

#include "ServerSession.h"

#define HANDLER_DECL( p )			static VOID On##p( ServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize )
#define HANDLER_IMPL( p )			VOID Handler_FromGameServer::On##p( ServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize )

class Handler_FromGameServer
{
public:
	Handler_FromGameServer(void);
	~Handler_FromGameServer(void);

	HANDLER_DECL( AL_Login_ANC );
};

#endif
