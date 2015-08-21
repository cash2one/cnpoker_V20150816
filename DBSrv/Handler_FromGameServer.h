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

	HANDLER_DECL( GD_Login_REQ );
	HANDLER_DECL( GD_Logout_REQ );
	HANDLER_DECL( GD_Save_CMD );
	HANDLER_DECL( GD_Update_CMD );
};


#endif
