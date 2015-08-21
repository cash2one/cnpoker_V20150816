#include "Handler_FromLoginServer.h"

#include "DBUser.h"
#include "DBFactory.h"
#include "DBUserManager.h"
#include "LoginServerQuery.h"


Handler_FromLoginServer::Handler_FromLoginServer() 
{
	
}

Handler_FromLoginServer::~Handler_FromLoginServer() 
{
	
}


HANDLER_IMPL( LD_Login_REQ )
{
	printf("Step1: <3> LD_Login_REQ\n");
	
	MSG_LD_LOGIN_REQ * pRecvMsg = (MSG_LD_LOGIN_REQ *)pMsg;
	// 传入消息包包含: m_pNetObj, m_byUsername, m_byPassword
	
	TCHAR szQueryBuff[1024];
	snprintf(szQueryBuff, sizeof(szQueryBuff), "call p_Login_Select(?,?);");
	Query_Login_update * pQuery = Query_Login_update::ALLOC();
	
	if (NULL != pQuery) 
	{
		pQuery->SetQuery( szQueryBuff );
		Obj_db_passport.QueryDirect( pQuery );
		
		int iSize = pQuery->vctRes.size();
		if (iSize == 1) 
		{
			// DB返回应答给 Login
			MSG_LD_LOGIN_ANC msg2;
			msg2.m_dwParameter = pRecvMsg->m_dwParameter; // UserKey
						
			msg2.m_uiRootID = pQuery->vctRes[0].uiRootID;
			msg2.m_pNetObj = pRecvMsg->m_pNetObj;
			//BYTE m_byUserKey[CODE_KEY_LEN + 1]; 	// 数据库获取方式??
			pServerSession->Send( (BYTE*)&msg2, sizeof(msg2) );
		}
		
		Query_Login_update::FREE( pQuery );
		pQuery = NULL;		
	}
}

HANDLER_IMPL( LD_Logout_REQ )
{
	printf("LD_Logout_REQ\n");
	
}
