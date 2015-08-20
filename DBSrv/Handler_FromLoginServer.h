#ifndef _HANDLER_FROMLOGINSERVER_H_INCLUDED_
#define _HANDLER_FROMLOGINSERVER_H_INCLUDED_

#include <Common.h>

#include "ServerSession.h"

#define HANDLER_DECL( p )			static VOID On##p( ServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize )
#define HANDLER_IMPL( p )			VOID Handler_FromLoginServer::On##p( ServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize )

class Handler_FromLoginServer
{
public:
	Handler_FromLoginServer(void);
	~Handler_FromLoginServer(void);

	HANDLER_DECL( LD_Login_REQ );
	HANDLER_DECL( LD_Logout_REQ );
};


#endif
