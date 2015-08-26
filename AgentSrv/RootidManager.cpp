#include "RootidManager.h"

RootidManager g_RootidManager;

RootidManager::RootidManager()
{
	//memset( this, 0, sizeof(RootidManager) );
	//m_mapRootid.clear();
}

RootidManager::~RootidManager()
{
	Release();
}

void RootidManager::Release()
{
	m_mapRootid.clear();
}

BOOL RootidManager::Init()
{
	m_mapRootid.clear();
	return TRUE;
}

BOOL RootidManager::AddRootID( RootID * pRoot )
{	
	MAP_ROOTID_ITER it = m_mapRootid.find( pRoot->GetRootID() );
	if ( it == m_mapRootid.end() ) {
		m_mapRootid[ pRoot->GetRootID() ] = pRoot;
		return TRUE;
	}
	return FALSE;
}

RootID * RootidManager::FindRootID( const DWORD dwRootID )
{
	MAP_ROOTID_ITER it = m_mapRootid.find(dwRootID);
	if (it != m_mapRootid.end()) {
		return it->second;
	}
	return NULL;
}

BOOL RootidManager::RemoveRootID( const DWORD dwRootID )
{
	MAP_ROOTID_ITER it = m_mapRootid.find(dwRootID);
	if (it == m_mapRootid.end()) {
		return FALSE;
	}
	m_mapRootid.erase(it);
	
	return TRUE;
}
