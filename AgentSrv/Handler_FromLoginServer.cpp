#include "Handler_FromLoginServer.h"
#include "AgentServer.h"
#include "User.h"
#include "UserManager.h"

Handler_FromLoginServer::Handler_FromLoginServer() 
{
	
}

Handler_FromLoginServer::~Handler_FromLoginServer() 
{
	
}

HANDLER_IMPL( AL_Prelogin_ANC )
{
	MSG_AL_PRELOGIN_ANC * pObj = (MSG_AL_PRELOGIN_ANC *) pMsg;
	
	User * pUser = g_UserManager.FindUser(pObj->m_dwParameter);
	if ( pUser == NULL ) {
		printf("g_UserManager.FindUser(%d) Fail\n", pObj->m_dwParameter);
		return;
	}
	
	MSG_CA_PRELOGIN_GAME_ANC msg2;
	msg2.uiRootID = pObj->uiRootID;
	memcpy(msg2.byUserKey, pObj->byUserKey, sizeof(pObj->byUserKey) );
	memcpy(msg2.m_byIP, pObj->m_byIP, sizeof(pObj->m_byIP) );
	msg2.m_Port = pObj->m_Port;
	pUser->SendPacket( (BYTE *) &msg2, wSize );
}

HANDLER_IMPL( AL_Login_ANC )
{
	MSG_AL_LOGIN_ANC * pObj = (MSG_AL_LOGIN_ANC *) pMsg;
	
	User * pUser = g_UserManager.FindUser(pObj->m_dwParameter);
	if ( pUser == NULL ) {
		printf("g_UserManager.FindUser(%d) Fail\n", pObj->m_dwParameter);
		return;
	}
	
	MSG_AG_LOGIN_REQ msg2;
	msg2.m_uiRootID = pObj->uiRootID;
	g_AgentServer->SendToGameServer( (BYTE *)&msg2, sizeof(msg2) );
}

