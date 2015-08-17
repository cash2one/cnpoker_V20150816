#include "Handler_FromGameServer.h"

#include "User.h"
#include "UserManager.h"

Handler_FromGameServer::Handler_FromGameServer() 
{
	
}

Handler_FromGameServer::~Handler_FromGameServer() 
{
	
}

HANDLER_IMPL( AG_StartGame_ANC )
{
	printf("Recv GameServer Msg --> AG_StartGame_ANC Success\n");
	MSG_AG_START_GAME_ANC * pRecv = (MSG_AG_START_GAME_ANC *)pMsg;
	printf("%d ?= 40, %d ?= 2001, UserKey=%d\n", pRecv->m_byCategory, pRecv->m_byProtocol, pRecv->m_dwUserID);
	
	User * pUser = g_UserManager.FindUser(pRecv->m_dwUserID);
	if ( pUser == NULL ) {
		printf("g_UserManager.FindUser(%d) Fail\n", pRecv->m_dwUserID);
		return;
	}
	
	pUser->SendPacket( (BYTE *)pMsg, wSize );
}

#if 0
HANDLER_IMPL( AG_Heartbeat_SYN )
{
	
}

HANDLER_IMPL( AG_Logout_REQ)
{

}

HANDLER_IMPL( AG_Relogin_SYN )
{
	
}

HANDLER_IMPL( AG_Logout_REQ)
{
	
}

HANDLER_IMPL( AG_StartGame_REQ )
{
	
}

HANDLER_IMPL( AG_JoinRoom_REQ )
{
	
}

HANDLER_IMPL( AG_JoinTable_REQ )
{
	
}

HANDLER_IMPL( AG_ShowCards_REQ )
{
	
}

HANDLER_IMPL( AG_Discards_REQ )
{
	
}

HANDLER_IMPL( AG_EndGame_REQ )
{
		
}
#endif
