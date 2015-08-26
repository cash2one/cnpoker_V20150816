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


HANDLER_IMPL( GD_Login_REQ )
{
	printf("Step2: <3> GD_Login_REQ\n");
	MSG_GD_LOGIN_REQ * pRecvMsg = (MSG_GD_LOGIN_REQ *)pMsg;
	
	GameServerSession * pSession = (GameServerSession *) pServerSession;
	DBUser * pUser = DBFactory::Instance()->AllocDBUser(); // 分配 DBUser
	if ( pUser != NULL ) {		
		pUser->SetHashKey( pRecvMsg->m_dwParameter ); // User ID
		pUser->SetRootID( pRecvMsg->m_uiRootID );
		pSession->AddUser( pUser ); // GameServerSession 对 DBUser 进行管理
	
		TCHAR szQueryBuff[1024];
		snprintf(szQueryBuff, sizeof(szQueryBuff), "call g_GamePack_Query(%d)", pRecvMsg->m_uiRootID);
		Query_GamePackage_select * pQuery = Query_GamePackage_select::ALLOC(); // Query_GamePackage_update
		
		if (NULL != pQuery) 
		{
			pQuery->SetQuery( szQueryBuff );
			pQuery->pParam[0].m_uiRootID = pRecvMsg->m_uiRootID;
			Obj_db_passport.QueryDirect( pQuery );
			
			int iSize = pQuery->vctRes.size();
			if (iSize == 1) {
				// 返回应答消息给 Game
				MSG_GD_LOGIN_ANC pANC;
				pANC.m_dwParameter = pRecvMsg->m_dwParameter;
				
				pANC.m_uiRootID 	= pRecvMsg->m_uiRootID;
				pANC.m_uiScore 		= pQuery->vctRes[0].m_uiScore;
				pANC.m_uiFaileds	= pQuery->vctRes[0].m_uiFaileds;
				pANC.m_uiWons		= pQuery->vctRes[0].m_uiWons;
				pANC.m_uiEscape 	= pQuery->vctRes[0].m_uiEscape;
				pServerSession->Send( (BYTE*)&pANC, sizeof(pANC) );
				
				// 同时更新 DBUser 里的 游戏信息
				pUser->GetGameInfo().m_uiRootID 	= pANC.m_uiRootID ;
				pUser->GetGameInfo().m_uiScore 		= pANC.m_uiScore;
				pUser->GetGameInfo().m_uiFaileds 	= pANC.m_uiFaileds;
				pUser->GetGameInfo().m_uiWons 		= pANC.m_uiWons;
				pUser->GetGameInfo().m_uiEscape 	= pANC.m_uiEscape;
			}
			else {
				printf("Error: Get Game User info fail\n");
				// 发送错误消息
				// MSG_
			}
			
			Query_GamePackage_select::FREE( pQuery );
			pQuery = NULL;		
		}
	}
}

HANDLER_IMPL( GD_Logout_REQ )
{
	MSG_GD_LOGOUT_REQ * pLogout = (MSG_GD_LOGOUT_REQ *)pMsg;
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
		pUser->GetGameInfo().m_uiScore 		= pSave->uiScore  ;
		pUser->GetGameInfo().m_uiFaileds 	= pSave->uiFaileds;
		pUser->GetGameInfo().m_uiWons 		= pSave->uiWons	  ;
		pUser->GetGameInfo().m_uiEscape 	= pSave->uiEscape ;
		
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