#include "Handler_FromAgentServer.h"

#include "LoginServer.h"
#include "LoginUserManager.h"

#include <Network.h>


Handler_FromAgentServer::Handler_FromAgentServer() 
{
	
}

Handler_FromAgentServer::~Handler_FromAgentServer() 
{
	
}

HANDLER_IMPL( AL_PreLogin_REQ )
{
	printf("Step1: <2> AL_PreLogin_REQ\n");
	
	MSG_AL_PRELOGIN_REQ * pRecvMsg = (MSG_AL_PRELOGIN_REQ *)pMsg;
	
	MSG_LD_LOGIN_REQ msg2;
	msg2.m_dwParameter = pRecvMsg->m_dwParameter;
	msg2.m_pNetObj = (NetworkObject *) pServerSession;
	
	memcpy(msg2.m_byUsername, pRecvMsg->m_byUsername, sizeof(pRecvMsg->m_byUsername) );
	memcpy(msg2.m_byPassword, pRecvMsg->m_byPassword, sizeof(pRecvMsg->m_byPassword) );
	
	g_LoginServer->SendToDBServer( (BYTE *)&msg2, sizeof(MSG_LD_LOGIN_REQ) );
}

HANDLER_IMPL( AL_ReLogin_REQ )
{
	printf("AL_ReLogin_REQ\n");
	
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

HANDLER_IMPL( AL_Login_REQ )
{
	printf("Step2: <2> AL_Login_REQ\n");
	
	MSG_AL_LOGIN_REQ * pRecvMsg = (MSG_AL_LOGIN_REQ *)pMsg;
	
	// 在LoginUserManager中查找用户
	LoginUser * pLoginUser = LoginUserManager::Instance()->POP(pRecvMsg->m_uiRootID); // POP的时候已在 LoginUserManager Map中擦除
	if (pLoginUser != NULL) {
		// Login验证 m_byUserKey
		BOOL bRet = pLoginUser->IsSameMD(pRecvMsg->m_byUserKey);
		if ( !bRet ) {
			printf("Error: Not the Same MD.\n");
			// 返回登陆失败 消息包
			// MSG_
		}
		
		AgentServerSession * pSession = (AgentServerSession *)pServerSession;
		if ( pSession != NULL ) {
			pSession->m_userCount++; // 用户数量+1;
			LoginFactory::Instance()->FreeLoginUser(pLoginUser); // 释放 登陆用户
			
			// 返回消息包给Agent
			MSG_AL_LOGIN_ANC pSendMsg;
			pSendMsg.m_uiRootID = pRecvMsg->m_uiRootID;
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
		printf("Error: AL_Login_REQ Fail\n");
		// 返回登陆失败 消息包
		// MSG_
	}
}


HANDLER_IMPL( AL_Logout_REQ )
{
	printf("AL_Logout_REQ\n");
	
	AgentServerSession * pSession = (AgentServerSession *)pServerSession;
	pSession->m_userCount--;
	
	MSG_AL_LOGOUT_REQ * pRecvMsg = (MSG_AL_LOGOUT_REQ *) pMsg;
	
	MSG_LD_LOGOUT_REQ pSendMsg;
	pSendMsg.m_uiRootID = pRecvMsg->m_uiRootID;
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