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
	MSG_AL_PRELOGIN_SYN * pObj = (MSG_AL_PRELOGIN_SYN *) pMsg;
	
	MSG_LD_LOGIN_SYN pSync;
	pSync.netObj = (NetworkObject *) pServerSession;
	
	memcpy(pSync.byUsername, pObj->byUsername, sizeof(pObj->byUsername) );
	memcpy(pSync.byPassword, pObj->byPassword, sizeof(pObj->byPassword) );
	
	g_LoginServer->SendToDBServer( (BYTE *)&pSync, sizeof(MSG_LD_LOGIN_SYN) );
}

HANDLER_IMPL( AL_Relogin_SYN )
{
/*	
	MSG_AL_RELOGIN_SYN * pObj = (MSG_AL_RELOGIN_SYN *) pMsg;
	
	LoginUser * pLoginUser = NULL;
	pLoginUser = LoginFactory::Instance()->AllocLoginUser();
	
	if ( pLoginUser != NULL ) {
		AgentServerSession * pSession = (AgentServerSession *) pServerSession;
		if ( pSession != NULL ) {
			pLoginUser->SetRootID(pObj->uiRootID);
			pLoginUser->SetMD(pObj->byUserKey);
			LoginUserManager::Instance()->PUSH(pLoginUser);
			return;
		}
	}
*/
}

HANDLER_IMPL( AL_Login_SYN )
{
	LoginUser * pLoginUser = NULL;
	MSG_AL_LOGIN_SYN * pObj = (MSG_AL_LOGIN_SYN *) pMsg;
	
	pLoginUser = LoginUserManager::Instance()->POP(pObj->uiRootID);
	if (pLoginUser != NULL) {
		AgentServerSession * pSession = (AgentServerSession *)pServerSession;
		if ( pSession != NULL ) {
			pSession->m_dwLoginCount++;
			LoginFactory::Instance()->FreeLoginUser(pLoginUser);
			
			MSG_AL_LOGIN_ANC pSendMsg;
			pSendMsg.uiRootID = pObj->uiRootID;
			pSession->Send( (BYTE *)&pSendMsg, sizeof(pSendMsg) );
			return;
		}
		
		// @{ Save its after Login; }
		// pLoginUser->SetRootID(pObj->m_dwParameter);
		// pSession->AddUser(pLoginUser);
	}
	else 
	{
		// 登录失败
	}
}


HANDLER_IMPL( AL_Logout_SYN )
{
	AgentServerSession * pSession = (AgentServerSession *)pServerSession;
	pSession->m_dwLoginCount--;
	
	MSG_AL_LOGOUT_SYN * pObj = (MSG_AL_LOGOUT_SYN *) pMsg;
	
	MSG_LD_LOGOUT_SYN pSendMsg;
	pSendMsg.uiRootID = pObj->uiRootID;
	g_LoginServer->SendToDBServer( (BYTE *)&pSendMsg, sizeof(pSendMsg) );
	
	/*
	pLoginUser = LoginUserManager::Instance()->POP(pObj->uiRootID);
	if (pLoginUser != NULL) {
		AgentServerSession * pSession = (AgentServerSession *)pServerSession;
		pSession->m_dwLoginCount--;
		
		// @{ Save its after Login; }
		// pSession->RemoveUser( pLoginUser->GetHashKey() );
	}
	*/
}