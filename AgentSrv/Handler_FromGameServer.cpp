#include "Handler_FromGameServer.h"

#include "User.h"
#include "UserManager.h"

Handler_FromGameServer::Handler_FromGameServer() 
{
	
}

Handler_FromGameServer::~Handler_FromGameServer() 
{
	
}

HANDLER_IMPL( GA_StartGame_ANC )
{
	printf("Recv GameServer Msg --> GA_StartGame_ANC Success\n");
	MSG_GA_START_GAME_ANC * pRecv = (MSG_GA_START_GAME_ANC *)pMsg;
	printf("%d ?= 40, %d ?= 2001, UserKey=%d\n", pRecv->m_byCategory, pRecv->m_byProtocol, pRecv->m_dwUserKey);
	
	User * pUser = g_UserManager.FindUser(pRecv->m_dwUserKey);
	if ( pUser == NULL ) {
		printf("g_UserManager.FindUser(%d) Fail\n", pRecv->m_dwUserKey);
		return;
	}
	
	pUser->SendPacket( (BYTE *)pMsg, wSize );
}

#if 0
HANDLER_IMPL( GA_Heartbeat_SYN )
{
	
}

HANDLER_IMPL( GA_Logout_REQ)
{

}

HANDLER_IMPL( GA_Relogin_SYN )
{
	
}

HANDLER_IMPL( GA_Logout_REQ)
{
	
}

HANDLER_IMPL( GA_StartGame_REQ )
{
	
}

HANDLER_IMPL( GA_JoinRoom_REQ )
{
	
}

HANDLER_IMPL( GA_JoinTable_REQ )
{
	
}

HANDLER_IMPL( GA_ShowCards_REQ )
{
	
}

HANDLER_IMPL( GA_Discards_REQ )
{
	
}

HANDLER_IMPL( GA_EndGame_REQ )
{
		
}
#endif
