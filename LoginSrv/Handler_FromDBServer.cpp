#include "Handler_FromDBServer.h"
#include "LoginUserManager.h"
#include "LoginFactory.h"
#include "LoginUser.h"

Handler_FromDBServer::Handler_FromDBServer() 
{
	
}

Handler_FromDBServer::~Handler_FromDBServer() 
{
	
}


HANDLER_IMPL( LD_Login_ANC )
{
	MSG_LD_LOGIN_ANC * pObj = (MSG_LD_LOGIN_ANC *) pMsg;
	
	LoginUser * pLoginUser = NULL;
	pLoginUser = LoginFactory::Instance()->AllocLoginUser();
	
	if ( pLoginUser != NULL ) {
		AgentServerSession * pSession = (AgentServerSession *) pObj->netObj;
		if ( pSession != NULL ) {
			pLoginUser->SetRootID(pObj->uiRootID);
			pLoginUser->SetMD(pObj->byUserKey);
			LoginUserManager::Instance()->PUSH(pLoginUser);
			
			MSG_AL_PRELOGIN_ANC pSendMsg;
			pSendMsg.m_dwParameter 	= pObj->m_dwParameter;
			pSendMsg.uiRootID 		= pObj->uiRootID;
			memset( pSendMsg.byUserKey, pObj->byUserKey, CODE_KEY_LEN);
			pSession->Send( (BYTE *)&pSendMsg, sizeof(pSendMsg) );
		}
	}
}


HANDLER_IMPL( LD_Logout_ANC )
{
	
}