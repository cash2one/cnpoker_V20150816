#include "Handler_FromLoginServer.h"
#include "AgentServer.h"
#include "User.h"
#include "UserManager.h"

#include "RootidManager.h"

Handler_FromLoginServer::Handler_FromLoginServer() 
{
	
}

Handler_FromLoginServer::~Handler_FromLoginServer() 
{
	
}

HANDLER_IMPL( AL_PreLogin_ANC )
{
	printf("Step1: <5> AL_Prelogin_ANC\n");
	MSG_AL_PRELOGIN_ANC * pRecvMsg = (MSG_AL_PRELOGIN_ANC *) pMsg;
	
	User * pUser = g_UserManager.FindUser(pRecvMsg->m_dwParameter);
	if ( pUser == NULL ) {
		printf("g_UserManager.FindUser(%d) Fail\n", pRecvMsg->m_dwParameter);
		return;
	}
	
	// 返回信息给 Client
	MSG_CA_PRELOGIN_ANC msg2;
	msg2.m_uiRootID = pRecvMsg->m_uiRootID;
	msg2.m_dwPort = pRecvMsg->m_dwPort;
	memcpy(msg2.m_byUserKey, pRecvMsg->m_byUserKey, sizeof(pRecvMsg->m_byUserKey) );
	memcpy(msg2.m_byIP, pRecvMsg->m_byIP, sizeof(pRecvMsg->m_byIP) );
	printf("m_byUserKey=%s, m_byIP=%s, m_dwPort = %d\n", msg2.m_byUserKey, msg2.m_byIP, msg2.m_dwPort);
	msg2.m_dwPort = pRecvMsg->m_dwPort;
	pUser->SendPacket( (BYTE *) &msg2, wSize );
}

HANDLER_IMPL( AL_Login_ANC )
{
	printf("Step2: <3> AL_Login_ANC\n");
	MSG_AL_LOGIN_ANC * pRecvMsg = (MSG_AL_LOGIN_ANC *) pMsg;
	
	User * pUser = g_UserManager.FindUser(pRecvMsg->m_dwParameter);
	if ( pUser == NULL ) {
		printf("g_UserManager.FindUser(%d) Fail\n", pRecvMsg->m_dwParameter);
		return;
	}
	
	// 连接到Game
	MSG_AG_LOGIN_REQ msg2;
	msg2.m_uiRootID = pRecvMsg->m_uiRootID;
	g_AgentServer->SendToGameServer( (BYTE *)&msg2, sizeof(msg2) );
}

HANDLER_IMPL( AL_SaveUserKey_SYN )
{
	printf("AL_SaveUserKey_SYN\n");
	MSG_AL_SAVEUSERKEY_SYN * pRecvMsg = (MSG_AL_SAVEUSERKEY_SYN *)pMsg;
	printf("RootID = %d, User Key = %s\n", pRecvMsg->m_uiRootID, pRecvMsg->m_byUserKey);
	
	RootID * pRoot = AgentFactory::Instance()->AllocRootID();
	if ( pRoot == NULL ) {
		printf("\nAgentFactory::Instance()->AllocRootID() Fail.\n");
		return;
	}
	pRoot->SetRootID(pRecvMsg->m_uiRootID);
	pRoot->SetUserKey(pRecvMsg->m_byUserKey);
	
	
	BOOL bRet = RootidManager::Instance()->AddRootID(pRoot);
	if ( !bRet ) {
		printf("\n[RootidManager::Instance()->AddRootID] Fail.\n");
		return;
	}
	printf("[RootidManager::Instance()->AddRootID] Success.\n");
}
