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
	printf("Step1: <4> LD_Login_ANC\n");
	
	MSG_LD_LOGIN_ANC * pRecvMsg = (MSG_LD_LOGIN_ANC *) pMsg;

	// 分配用户,保存信息，下次正式登陆时需要对比(主要验证 m_byUserKey )
	LoginUser * pLoginUser = LoginFactory::Instance()->AllocLoginUser();
	
	if ( pLoginUser != NULL ) {
		AgentServerSession * pSession = (AgentServerSession *) pRecvMsg->m_pNetObj;
		if ( pSession != NULL ) {
			pLoginUser->SetRootID(pRecvMsg->m_uiRootID);
			pLoginUser->SetMD(pRecvMsg->m_byUserKey);
			LoginUserManager::Instance()->PUSH(pLoginUser); // 根据RootID来查找LoginUser，组成一个map
			
			MSG_AL_PRELOGIN_ANC msg2;
			msg2.m_dwParameter 	= pRecvMsg->m_dwParameter; // dwUserKey
			msg2.m_uiRootID 	= pRecvMsg->m_uiRootID;
			memcpy( msg2.m_byUserKey, pRecvMsg->m_byUserKey, CODE_KEY_LEN); // 
			
			AgentServerSession * pSession = AllocServer::Instance()->POP(); // 什么时候PUSH 进去的???
			// 我的理解是Login服务器在初始化时读配置文件， 然后AllocAgent, 把IP，Port存进去。
			memcpy( msg2.m_byIP, pSession->GetConnnectIP().c_str(), pSession->GetConnnectIP().size() );
			msg2.m_dwPort = pSession->GetConnnectPort();
			pSession->Send( (BYTE *)&msg2, sizeof(msg2) );
			
			// 同时还要把这个LoginUser添加到LoginUserManager中管理
			LoginUserManager::Instance()->PUSH(pLoginUser);
		}
	}
}


HANDLER_IMPL( LD_Logout_ANC )
{
	
}