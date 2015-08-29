#include "Handler_FromGameServer.h"

#include "User.h"
#include "UserManager.h"

Handler_FromGameServer::Handler_FromGameServer() 
{
	
}

Handler_FromGameServer::~Handler_FromGameServer() 
{
	
}

HANDLER_IMPL( AG_Login_ANC )
{
	printf("Step2: <5> AG_Login_ANC\n");
	MSG_AG_LOGIN_ANC * pRecvMsg = (MSG_AG_LOGIN_ANC *)pMsg;
	
	// 查找用户
	User * pUser = g_UserManager.FindUser( pRecvMsg->m_dwParameter );
	if ( pUser == NULL ) {
		printf("g_UserManager.FindUser(%d) Fail\n", pRecvMsg->m_dwParameter);
		return;
	}
	
	// 返回应答消息给 Client
	MSG_CA_LOGIN_ANC msg2;
	//msg2.m_playerInfo.m_dwUserKey 		= pRecvMsg->m_dwParameter;
	msg2.m_playerInfo = pRecvMsg->m_playerInfo;
		
	pUser->SendPacket( (BYTE *)&msg2, wSize );
}

HANDLER_IMPL( AG_Logout_ANC )
{
	printf("Logout: <5> AG_Logout_ANC\n");
	MSG_AG_LOGOUT_ANC * pRecvMsg = (MSG_AG_LOGOUT_ANC *)pMsg;
	DWORD dwUserID = pRecvMsg->m_dwParameter;
	printf("UserID = %d\n", dwUserID);
	
	// 查找用户
	User * pUser = g_UserManager.FindUser( pRecvMsg->m_dwParameter );
	if ( pUser == NULL ) {
		printf("g_UserManager.FindUser(%d) Fail\n", pRecvMsg->m_dwParameter);
		return;
	}
	
	// 此处不释放。 在 DestroyClientSide 时释放
	
	// 返回应答消息给 Client
	MSG_CA_LOGOUT_ANC msg2;
	msg2.m_dwParameter = dwUserID;
	pUser->SendPacket( (BYTE *)&msg2, wSize );	
}

HANDLER_IMPL( AG_StartGame_ANC )
{
	printf("Recv GameServer Msg --> AG_StartGame_ANC Success\n");
	MSG_AG_START_GAME_ANC * pRecvMsg = (MSG_AG_START_GAME_ANC *)pMsg;
	//printf("%d ?= 40, %d ?= 2001, UserKey=%d\n", pRecvMsg->m_byCategory, pRecvMsg->m_byProtocol, pRecvMsg->m_dwParameter);
	
	User * pUser = g_UserManager.FindUser(pRecvMsg->m_dwParameter);
	if ( pUser == NULL ) {
		printf("g_UserManager.FindUser(%d) Fail\n", pRecvMsg->m_dwParameter);
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
