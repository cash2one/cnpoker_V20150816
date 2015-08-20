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

HANDLER_IMPL( AL_PreLogin_ANC )
{
	printf("AL_Prelogin_ANC\n");
	MSG_AL_PRELOGIN_ANC * pRecvMsg = (MSG_AL_PRELOGIN_ANC *) pMsg;
	
	User * pUser = g_UserManager.FindUser(pRecvMsg->m_dwParameter);
	if ( pUser == NULL ) {
		printf("g_UserManager.FindUser(%d) Fail\n", pRecvMsg->m_dwParameter);
		return;
	}
	
	MSG_CA_PRELOGIN_ANC msg2;
	msg2.m_uiRootID = pRecvMsg->m_uiRootID;
	memcpy(msg2.m_byUserKey, pRecvMsg->m_byUserKey, sizeof(pRecvMsg->m_byUserKey) );
	memcpy(msg2.m_byIP, pRecvMsg->m_byIP, sizeof(pRecvMsg->m_byIP) );
	msg2.m_dwPort = pRecvMsg->m_dwPort;
	pUser->SendPacket( (BYTE *) &msg2, wSize );
}

HANDLER_IMPL( AL_Login_ANC )
{
	MSG_AL_LOGIN_ANC * pRecvMsg = (MSG_AL_LOGIN_ANC *) pMsg;
	
	User * pUser = g_UserManager.FindUser(pRecvMsg->m_dwParameter);
	if ( pUser == NULL ) {
		printf("g_UserManager.FindUser(%d) Fail\n", pRecvMsg->m_dwParameter);
		return;
	}
	
	MSG_AG_LOGIN_REQ msg2;
	msg2.m_uiRootID = pRecvMsg->m_uiRootID;
	g_AgentServer->SendToGameServer( (BYTE *)&msg2, sizeof(msg2) );
}

