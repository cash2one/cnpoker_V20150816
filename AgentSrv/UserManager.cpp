//#include "UserFactory.h"
#include "UserManager.h"
#include "User.h"
#include <Const.h>
#include <Define.h>
//#include <LogMsg.h>

UserManager g_UserManager;

UserManager::UserManager()
	:	m_pUserHashTable ( NULL )
{
}

UserManager::~UserManager()
{
	//ASSERT( "ReleaseUser()." && m_pUserHashTable == NULL );	
}

VOID UserManager::InitUserSize( DWORD dwUserSize )
{
	m_pUserHashTable = new SolarHashTable<User *>;
	m_pUserHashTable->Initialize( dwUserSize );

	m_UserKey.Create(1, dwUserSize*2);

	assert( m_UserAuthIDs.empty() );
}

DWORD UserManager::AddUser( User * pUser )
{
	assert( pUser != NULL );
	DWORD dwUserKey = AllocKey();
	m_pUserHashTable->Add( pUser, dwUserKey );
	return dwUserKey;
}

DWORD UserManager::GetUserNums()
{
	return m_pUserHashTable->GetDataNum();
}

User * UserManager::FindUser( DWORD dwUserKey )
{
	return m_pUserHashTable->GetData( dwUserKey );
}

void UserManager::Remove( DWORD dwUserKey )
{
	User * pUser = m_pUserHashTable->GetData( dwUserKey );
	assert( pUser != NULL );
	if( NULL == pUser)
	{
		printf("[UserManager::Remove] User[%d] is NULL!!", dwUserKey);
		return;
	}	
	m_pUserHashTable->Remove( dwUserKey );	
	m_UserKey.RestoreKey( dwUserKey );
	printf("[UserManager::Remove] User Key : %d\n", dwUserKey);
}

void UserManager::Remove( User * pUser )
{
	printf("Do nothing\n");
}
