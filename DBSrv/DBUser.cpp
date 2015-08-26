#include "DBUser.h"
#include "GameServerQuery.h"

DBUser::DBUser()
{
	memset( this, 0, sizeof(DBUser) );
}

DBUser::~DBUser()
{
}

void DBUser::Login(unsigned int rootID)
{
	m_dwRootID = rootID;
}
	
void DBUser::Logout(unsigned int rootID)
{
	
}

BOOL DBUser::UpdateToDB()
{
	TCHAR szQueryBuff[1024];
	snprintf(szQueryBuff, sizeof(szQueryBuff), "call p_GamePake_Query(?);");
	Query_GamePackage_update * pQuery = Query_GamePackage_update::ALLOC();
	
	if (NULL != pQuery) 
	{
		pQuery->SetQuery( szQueryBuff );
		pQuery->pParam[0].m_uiRootID = m_sInfo.m_uiRootID;
		pQuery->pParam[0].m_uiScore = m_sInfo.m_uiScore;
		pQuery->pParam[0].m_uiFaileds = m_sInfo.m_uiFaileds;
		pQuery->pParam[0].m_uiWons = m_sInfo.m_uiWons;
		pQuery->pParam[0].m_uiEscape = m_sInfo.m_uiEscape;
		Obj_db_passport.QueryDirect( pQuery );
		
		int iSize = pQuery->vctRes.size();
		if (iSize == 1)
		{
			return TRUE;
		}
		
		Query_GamePackage_update::FREE( pQuery );
		pQuery = NULL;		
	}
	return FALSE;
}