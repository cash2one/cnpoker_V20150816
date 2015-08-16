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
	Query_GamePackage_select * pQuery = Query_GamePackage_select::ALLOC();
	
	if (NULL != pQuery) 
	{
		pQuery->SetQuery( szQueryBuff );
		pQuery->pParam[0].uiRootID = m_sInfo.uiRootID;
		pQuery->pParam[0].uiRootID = m_sInfo.uiScore;
		pQuery->pParam[0].uiRootID = m_sInfo.uiFaileds;
		pQuery->pParam[0].uiRootID = m_sInfo.uiWons;
		pQuery->pParam[0].uiRootID = m_sInfo.uiEscape;
		Obj_db_passport.QueryDirect( pQuery );
		
		int iSize = pQuery->vctRes.size();
		if (iSize == 1)
		{
			return TRUE;
		}
		
		Query_GamePackage_select::FREE( pQuery );
		pQuery = NULL;		
	}
	return FALSE;
}