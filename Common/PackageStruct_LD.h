#ifndef _PACKAGESTRUCT_LD_H_INCLUDED_
#define _PACKAGESTRUCT_LD_H_INCLUDED_

#include <Network.h>
#include "PackageStruct.h"
#include "Protocol_LD.h"
#include "Define.h"

#pragma pack(push, 1)

struct MSG_LD_LOGIN_SYN : public MSG_BASE_FORWARD
{
	BYTE byUsername[32];
	BYTE byPassword[32];
	NetworkObject * netObj;
	
	MSG_LD_LOGIN_SYN()
	{
		memset( this, 0, sizeof(MSG_LD_LOGIN_SYN) );
		
		m_byCategory = LD_ClientLogin;
		m_byProtocol = LD_Login_SYN;
	}
};

struct MSG_LD_LOGIN_ANC : public MSG_BASE_FORWARD
{
	unsigned int uiRootID;
	BYTE byUserKey[CODE_KEY_LEN + 1];
	NetworkObject * netObj;
	
	MSG_LD_LOGIN_ANC()
	{
		memset( this, 0, sizeof(MSG_LD_LOGIN_ANC) );
		
		m_byCategory = LD_ClientLogin;
		m_byProtocol = LD_Login_ANC;
	}
};

struct MSG_LD_LOGOUT_SYN : public MSG_BASE_FORWARD
{
	unsigned int uiRootID;
	
	MSG_LD_LOGOUT_SYN()
	{
		memset( this, 0, sizeof(MSG_LD_LOGOUT_SYN) );
		
		m_byCategory = LD_ClientLogin;
		m_byProtocol = LD_Logout_SYN;
	}
};

#pragma pack(pop)

#endif // _PACKAGESTRUCT_CA_H_
