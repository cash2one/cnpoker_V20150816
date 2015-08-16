#include "LoginUserManager.h"

LoginUserManager::LoginUserManager()
{
	//memset( this, 0, sizeof(DBUserManager) );
}

LoginUserManager::~LoginUserManager()
{
	Release();
}

void LoginUserManager::Release()
{
	m_mapLoginUser.clear();
}

BOOL LoginUserManager::Init()
{
	m_mapLoginUser.clear();
	return TRUE;
}

void LoginUserManager::PUSH(LoginUser * pObj)
{
	MAP_LOGINUSER_ITER it = m_mapLoginUser.find( pObj->GetRootID() );
	if ( it != m_mapLoginUser.end() )
	{
		m_mapLoginUser[ pObj->GetRootID() ] = pObj;
	}
}

LoginUser * LoginUserManager::POP(DWORD dwRootID)
{
	MAP_LOGINUSER_ITER it = m_mapLoginUser.find( dwRootID );
	if ( it != m_mapLoginUser.end() )
	{
		LoginUser * pObj = it->second;
		m_mapLoginUser.erase(it);
		return pObj;
	}
}
