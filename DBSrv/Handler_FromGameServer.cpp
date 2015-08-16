#include "DBUser.h"
#include "DBFactory.h"
#include "DBUserManager.h"
#include "GameServerQuery.h"
#include "Handler_FromGameServer.h"

Handler_FromGameServer::Handler_FromGameServer() 
{
	
}

Handler_FromGameServer::~Handler_FromGameServer() 
{
	
}


HANDLER_IMPL( GD_Login_SYN )
{
	MSG_GD_LOGIN_SYN * pLogin = (MSG_GD_LOGIN_SYN *)pMsg;
	
	GameServerSession * pSession = (GameServerSession *) pServerSession;
	DBUser * pUser = DBFactory::Instance()->AllocDBUser();
	
	if ( pUser != NULL ) {
		pUser->SetHashKey( pLogin->m_dwParameter );
		pUser->SetRootID( pLogin->uiRootID );
		pSession->AddUser( pUser );
	
		TCHAR szQueryBuff[1024];
		snprintf(szQueryBuff, sizeof(szQueryBuff), "call p_GamePake_Query(?);");
		Query_GamePackage_select * pQuery = Query_GamePackage_select::ALLOC();
		
		if (NULL != pQuery) 
		{
			pQuery->SetQuery( szQueryBuff );
			pQuery->pParam[0].uiRootID = pLogin->uiRootID;
			Obj_db_passport.QueryDirect( pQuery );
			
			int iSize = pQuery->vctRes.size();
			if (iSize == 1)
			{
				MSG_GD_LOGIN_ANC pANC;
				pANC.m_dwParameter = pLogin->m_dwParameter;
				
				pANC.uiRootID 	= pLogin->uiRootID;
				pANC.uiScore	= pQuery->vctRes[0].uiScore;
				pANC.uiFaileds	= pQuery->vctRes[0].uiFaileds;
				pANC.uiWons		= pQuery->vctRes[0].uiWons;
				pANC.uiEscape	= pQuery->vctRes[0].uiEscape;
				pServerSession->Send( (BYTE*)&pANC, sizeof(pANC) );
				
				pUser->GetGameInfo().uiRootID	= pANC.uiRootID ;
				pUser->GetGameInfo().uiScore	= pANC.uiScore	;
				pUser->GetGameInfo().uiFaileds	= pANC.uiFaileds;
				pUser->GetGameInfo().uiWons		= pANC.uiWons	;
				pUser->GetGameInfo().uiEscape	= pANC.uiEscape	;
			}
			
			Query_GamePackage_select::FREE( pQuery );
			pQuery = NULL;		
		}
	}
}

HANDLER_IMPL( GD_Logout_SYN )
{
	MSG_GD_LOGOUT_SYN * pLogout = (MSG_GD_LOGOUT_SYN *)pMsg;
	// pLogout->uiRootID;
	
	GameServerSession * pSession = (GameServerSession *) pServerSession;
	DBUser * pUser = pSession->FindUser( pLogout->m_dwParameter );
	if (pUser != NULL) {
		DBFactory::Instance()->FreeDBUser(pUser);
		pSession->RemoveUser( pLogout->m_dwParameter );
	}
}

HANDLER_IMPL( GD_Save_CMD )
{
	MSG_GD_SAVE_CMD * pSave = (MSG_GD_SAVE_CMD *)pMsg;
	
	GameServerSession * pSession = (GameServerSession *) pServerSession;
	DBUser * pUser = pSession->FindUser( pSave->m_dwParameter );
	
	if (pUser != NULL) 
	{
		pUser->GetGameInfo().uiScore	= pSave->uiScore  ;
		pUser->GetGameInfo().uiFaileds	= pSave->uiFaileds;
		pUser->GetGameInfo().uiWons		= pSave->uiWons	  ;
		pUser->GetGameInfo().uiEscape	= pSave->uiEscape ;
		
		MSG_GD_SAVE_ANC pANC; 
		pANC.m_dwParameter = pSave->m_dwParameter;
		pServerSession->Send( (BYTE*)&pANC, sizeof(pANC) );
	}
}

HANDLER_IMPL( GD_Update_CMD )
{
	MSG_GD_UPDATE_CMD * pUpdate = (MSG_GD_UPDATE_CMD *)pMsg;
	
	GameServerSession * pSession = (GameServerSession *) pServerSession;
	DBUser * pUser = pSession->FindUser( pUpdate->m_dwParameter );
	
	if (pUser != NULL) 
	{
		pUser->UpdateToDB();
		
		MSG_GD_UPDATE_ANC pANC;
		pANC.m_dwParameter = pUpdate->m_dwParameter;
		pServerSession->Send( (BYTE*)&pANC, sizeof(pANC) );
	}
}