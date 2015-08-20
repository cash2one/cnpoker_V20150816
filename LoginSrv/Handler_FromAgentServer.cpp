#include "Handler_FromAgentServer.h"
#include "LoginUserManager.h"
#include <Network.h>
#include "LoginServer.h"

Handler_FromAgentServer::Handler_FromAgentServer() 
{
	
}

Handler_FromAgentServer::~Handler_FromAgentServer() 
{
	
}

HANDLER_IMPL( AL_Prelogin_SYN )
{
	printf("AL_Prelogin_SYN\n");
	
	MSG_AL_PRELOGIN_SYN * pRecvMsg = (MSG_AL_PRELOGIN_SYN *) pMsg;
	
	MSG_LD_LOGIN_SYN pSync;
	pSync.netObj = (NetworkObject *) pServerSession;
	
	memcpy(pSync.byUsername, pRecvMsg->byUsername, sizeof(pRecvMsg->byUsername) );
	memcpy(pSync.byPassword, pRecvMsg->byPassword, sizeof(pRecvMsg->byPassword) );
	
	g_LoginServer->SendToDBServer( (BYTE *)&pSync, sizeof(MSG_LD_LOGIN_SYN) );
}

HANDLER_IMPL( AL_Relogin_SYN )
{
	printf("AL_Relogin_SYN\n");
	
/*	
	MSG_AL_RELOGIN_SYN * pRecvMsg = (MSG_AL_RELOGIN_SYN *) pMsg;
	
	LoginUser * pLoginUser = NULL;
	pLoginUser = LoginFactory::Instance()->AllocLoginUser();
	
	if ( pLoginUser != NULL ) {
		AgentServerSession * pSession = (AgentServerSession *) pServerSession;
		if ( pSession != NULL ) {
			pLoginUser->SetRootID(pRecvMsg->uiRootID);
			pLoginUser->SetMD(pRecvMsg->byUserKey);
			LoginUserManager::Instance()->PUSH(pLoginUser);
			return;
		}
	}
*/
}

HANDLER_IMPL( AL_Login_SYN )
{
	printf("AL_Login_SYN\n");
	
	LoginUser * pLoginUser = NULL;
	MSG_AL_LOGIN_SYN * pRecvMsg = (MSG_AL_LOGIN_SYN *) pMsg;
	
	pLoginUser = LoginUserManager::Instance()->POP(pRecvMsg->uiRootID);
	if (pLoginUser != NULL) {
		AgentServerSession * pSession = (AgentServerSession *)pServerSession;
		if ( pSession != NULL ) {
			pSession->m_userCount++;
			LoginFactory::Instance()->FreeLoginUser(pLoginUser);
			
			MSG_AL_LOGIN_ANC pSendMsg;
			pSendMsg.uiRootID = pRecvMsg->uiRootID;
			pSession->Send( (BYTE *)&pSendMsg, sizeof(pSendMsg) );
			return;
		}
		
		// @{ Save its after Login; }
		// pLoginUser->SetRootID(pRecvMsg->m_dwParameter);
		// pSession->AddUser(pLoginUser);
	}
	else 
	{
		// 登录失败
	}
}


HANDLER_IMPL( AL_Logout_SYN )
{
	printf("AL_Logout_SYN\n");
	
	AgentServerSession * pSession = (AgentServerSession *)pServerSession;
	pSession->m_userCount--;
	
	MSG_AL_LOGOUT_SYN * pRecvMsg = (MSG_AL_LOGOUT_SYN *) pMsg;
	
	MSG_LD_LOGOUT_SYN pSendMsg;
	pSendMsg.uiRootID = pRecvMsg->uiRootID;
	g_LoginServer->SendToDBServer( (BYTE *)&pSendMsg, sizeof(pSendMsg) );
	
	/*
	pLoginUser = LoginUserManager::Instance()->POP(pRecvMsg->uiRootID);
	if (pLoginUser != NULL) {
		AgentServerSession * pSession = (AgentServerSession *)pServerSession;
		pSession->m_dwLoginCount--;
		
		// @{ Save its after Login; }
		// pSession->RemoveUser( pLoginUser->GetHashKey() );
	}
	*/
}