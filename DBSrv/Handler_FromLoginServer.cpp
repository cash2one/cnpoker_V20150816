#include "DBUser.h"
#include "DBFactory.h"
#include "DBUserManager.h"
#include "LoginServerQuery.h"
#include "Handler_FromLoginServer.h"

Handler_FromLoginServer::Handler_FromLoginServer() 
{
	
}

Handler_FromLoginServer::~Handler_FromLoginServer() 
{
	
}


HANDLER_IMPL( LD_Login_SYN )
{
	MSG_LD_LOGIN_SYN * pLogin = (MSG_LD_LOGIN_SYN *)pMsg;

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
			MSG_LD_LOGIN_ANC pANC;
			pANC.m_dwParameter = pLogin->m_dwParameter;
			
			pANC.uiRootID = pQuery->vctRes[0].uiRootID;
			pServerSession->Send( (BYTE*)&pANC, sizeof(pANC) );
		}
		
		Query_Login_update::FREE( pQuery );
		pQuery = NULL;		
	}
	
}

HANDLER_IMPL( LD_Logout_SYN )
{
	
}
