#include "LoginUser.h"

LoginUser::LoginUser()
{
	
}

LoginUser::~LoginUser()
{
	
}

void LoginUser::SetMD(BYTE * _md5)
{
	assert (_md5 != NULL);
	
	for (int i=0; i<TICKET_LEN; ++i)
	{
		 m_byMD5[i] = _md5[i];
	}
}

BOOL LoginUser::IsSameMD(BYTE * _md5)
{
	assert (_md5 != NULL);
	
	for (int i=0; i<TICKET_LEN; ++i)
	{
		if ( _md5[i] != m_byMD5[i] )
		{
			goto GT_FALSE;
		}
	}
	return TRUE;
	
GT_FALSE:
	return FALSE;
}