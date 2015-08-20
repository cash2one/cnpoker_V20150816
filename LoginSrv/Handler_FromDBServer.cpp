#include "Handler_FromDBServer.h"
#include "LoginUserManager.h"
#include "LoginFactory.h"
#include "AllocServer.h"
#include "LoginUser.h"

Handler_FromDBServer::Handler_FromDBServer() 
{
	
}

Handler_FromDBServer::~Handler_FromDBServer() 
{
	
}

HANDLER_IMPL( LD_Login_ANC )
{
	printf("<4> LD_Login_ANC\n");
	
	MSG_LD_LOGIN_ANC * pRecvMsg = (MSG_LD_LOGIN_ANC *) pMsg;

	// 分配用户
	LoginUser * pLoginUser = LoginFactory::Instance()->AllocLoginUser();
	
	if ( pLoginUser != NULL ) {
		AgentServerSession * pSession = (AgentServerSession *) pRecvMsg->m_pNetObj;
		if ( pSession != NULL ) {
			pLoginUser->SetRootID(pRecvMsg->m_uiRootID);
			pLoginUser->SetMD(pRecvMsg->m_byUserKey);
			LoginUserManager::Instance()->PUSH(pLoginUser);
			
			MSG_AL_PRELOGIN_ANC msg2;
			msg2.m_dwParameter 	= pRecvMsg->m_dwParameter; // dwUserKey
			msg2.m_uiRootID 	= pRecvMsg->m_uiRootID;
			memcpy( msg2.m_byUserKey, pRecvMsg->m_byUserKey, CODE_KEY_LEN);
			
			AgentServerSession * pSession = AllocServer::Instance()->POP(); // ??? 什么
			memcpy( msg2.m_byIP, pSession->GetConnnectIP().c_str(), pSession->GetConnnectIP().size() );
			msg2.m_dwPort = pSession->GetConnnectPort();
			pSession->Send( (BYTE *)&msg2, sizeof(msg2) );
		}
	}
}


HANDLER_IMPL( LD_Logout_ANC )
{
	
}