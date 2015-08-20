#ifndef _PACKAGESTRUCT_LD_H_INCLUDED_
#define _PACKAGESTRUCT_LD_H_INCLUDED_

#include <Network.h>
#include "PackageStruct.h"
#include "Protocol_LD.h"

#pragma pack(push, 1)

struct MSG_LD_LOGIN_REQ : public MSG_BASE_FORWARD
{
	BYTE 	m_byUsername[32];
	BYTE 	m_byPassword[32];
	NetworkObject * m_pNetObj;
	
	MSG_LD_LOGIN_REQ()
	{
		memset( this, 0, sizeof(MSG_LD_LOGIN_REQ) );
		
		m_byCategory = LD_ClientLogin;
		m_byProtocol = LD_Login_REQ;
		
		m_dwParameter = 0; // dwUserID
		m_byParameter = 0;
		
		m_pNetObj = NULL;
	}
};

struct MSG_LD_LOGIN_ANC : public MSG_BASE_FORWARD
{
	DWORD m_uiRootID;
	BYTE m_byUserKey[CODE_KEY_LEN + 1];
	NetworkObject * m_pNetObj;
	
	MSG_LD_LOGIN_ANC()
	{
		memset( this, 0, sizeof(MSG_LD_LOGIN_ANC) );
		
		m_byCategory = LD_ClientLogin;
		m_byProtocol = LD_Login_ANC;
		
		m_dwParameter = 0; // dwUserID
		m_byParameter = 0;
		
		m_pNetObj = NULL;
	}
};

struct MSG_LD_LOGOUT_REQ : public MSG_BASE_FORWARD
{
	DWORD m_uiRootID;
	
	MSG_LD_LOGOUT_REQ()
	{
		memset( this, 0, sizeof(MSG_LD_LOGOUT_REQ) );
		
		m_byCategory = LD_ClientLogin;
		m_byProtocol = LD_Logout_REQ;
		
		m_dwParameter = 0; // dwUserID
		m_byParameter = 0;
	}
};

#pragma pack(pop)

#endif // _PACKAGESTRUCT_LD_H_INCLUDED_
