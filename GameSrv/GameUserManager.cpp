#include "GameUserManager.h"

GameUserManager g_GameUserManager;

GameUserManager::GameUserManager()
{
}

GameUserManager::~GameUserManager()
{
	Release();
}

void GameUserManager::Release()
{
	m_mapGameUser.clear();
}

BOOL GameUserManager::Init()
{
	m_mapGameUser.clear();
	return TRUE;
}

BOOL GameUserManager::AddUser( GameUser * pUser )
{
	MAP_GAMEUSER_ITER it = m_mapGameUser.find( pUser->GetHashKey() );
	if ( it == m_mapGameUser.end() ) {
		m_mapGameUser[ pUser->GetHashKey() ] = pUser;
		return TRUE;
	}
	
	return FALSE;
}

GameUser * GameUserManager::Find( const DWORD dwKey )
{
	MAP_GAMEUSER_ITER it = m_mapGameUser.find( dwKey );
	if ( it != m_mapGameUser.end() ) {
		return it->second;
	}
	
	return NULL;
}
	
BOOL GameUserManager::Remove( DWORD dwKey )
{
	MAP_GAMEUSER_ITER it = m_mapGameUser.find( dwKey );
	if ( it == m_mapGameUser.end() ) {
		return FALSE;
	}
	m_mapGameUser.erase( it );
	
	return TRUE;
}
