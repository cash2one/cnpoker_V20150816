#include "DBUserManager.h"

DBUserManager::DBUserManager()
{
	//memset( this, 0, sizeof(DBUserManager) );
}

DBUserManager::~DBUserManager()
{
	Release();
}

void DBUserManager::Release()
{
	m_mapDBUser.clear();
}

BOOL DBUserManager::Init()
{
	m_mapDBUser.clear();
	return TRUE;
}

BOOL DBUserManager::AddUser(DBUser * pUser)
{
	MAP_DBUSER_ITER it = m_mapDBUser.find( pUser->GetHashKey() );
	if ( it == m_mapDBUser.end() ) {
		m_mapDBUser[ pUser->GetHashKey() ] = pUser;
		return TRUE;
	}
	return FALSE;
}

DBUser * DBUserManager::Find(DWORD dwKey)
{
	MAP_DBUSER_ITER it = m_mapDBUser.find(dwKey);
	if (it == m_mapDBUser.end()) {
		return it->second;
	}
}
	
BOOL DBUserManager::Remove(DWORD dwKey )
{
	MAP_DBUSER_ITER it = m_mapDBUser.find(dwKey);
	if (it == m_mapDBUser.end()) {
		return FALSE;
	}
	m_mapDBUser.erase(it);
	return TRUE;
}
