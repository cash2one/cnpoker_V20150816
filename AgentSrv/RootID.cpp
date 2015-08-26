#include "RootID.h"

RootID::RootID()
{	
}

RootID::~RootID()
{
}

void RootID::Clear()
{
	m_dwRootID = 0;
	memset( m_byUserKey, 0, sizeof(m_byUserKey) );
}

//BYTE * RootID::GetUserKey() const
//{
//	return &m_byUserKey;
//}

void RootID::SetUserKey( BYTE * pUserKey )
{
	if ( pUserKey == NULL) {
		printf("[RootID::SetUserKey] pUserKey is NULL\n");
		return;
	}
	memcpy(m_byUserKey, pUserKey, CODE_KEY_LEN);
	m_byUserKey[CODE_KEY_LEN] = '\0';
}

BOOL RootID::IsSameUserKey( BYTE * pUserKey )
{
	if ( pUserKey == NULL) {
		printf("[RootID::IsSameUserKey] pUserKey is NULL\n");
		return FALSE;
	}
	
	for( int i=0; i<CODE_KEY_LEN; ++i )
	{
		if ( m_byUserKey[i] != pUserKey[i] ) {
			return FALSE;
		}
	}

	return TRUE;
}

