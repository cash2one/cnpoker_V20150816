#ifndef _PACKAGESTRUCT_AL_H_INCLUDED_
#define _PACKAGESTRUCT_AL_H_INCLUDED_

#include "PackageStruct.h"
#include "Protocol_AL.h"
#include "Define.h"

#pragma pack(push, 1)

struct MSG_AL_PRELOGIN_SYN : public MSG_BASE_FORWARD
{
	BYTE byUsername[32];
	BYTE byPassword[32];
	
	MSG_AL_PRELOGIN_SYN()
	{
		memset( this, 0, sizeof(MSG_AL_PRELOGIN_SYN) );
		
		m_byCategory = LD_ClientLogin;
		m_byProtocol = AL_Prelogin_SYN;
	}
};

struct MSG_AL_PRELOGIN_ANC : public MSG_BASE_FORWARD
{
	unsigned int uiRootID;
	BYTE byUserKey[CODE_KEY_LEN + 1];
	
	MSG_AL_PRELOGIN_ANC()
	{
		memset( this, 0, sizeof(MSG_AL_PRELOGIN_ANC) );
		
		m_byCategory = AL_ClientLogin;
		m_byProtocol = AL_PreLogin_ANC;
	}
};

struct MSG_AL_RELOGIN_SYN : public MSG_BASE_FORWARD
{
	unsigned int uiRootID;
	BYTE byUserKey[CODE_KEY_LEN + 1];
	
	MSG_AL_RELOGIN_SYN()
	{
		memset( this, 0, sizeof(MSG_AL_RELOGIN_SYN) );
		
		m_byCategory = LD_ClientLogin;
		m_byProtocol = AL_Relogin_SYN;
	}
};

struct MSG_AL_RELOGIN_ANC : public MSG_BASE_FORWARD
{
	unsigned int uiRootID;
	
	MSG_AL_RELOGIN_ANC()
	{
		memset( this, 0, sizeof(MSG_AL_RELOGIN_ANC) );
		
		m_byCategory = AL_ClientLogin;
		m_byProtocol = AL_ReLogin_ANC;
	}
};


struct MSG_AL_LOGIN_SYN : public MSG_BASE_FORWARD
{
	unsigned int uiRootID;
	BYTE byUserKey[CODE_KEY_LEN + 1];
	
	MSG_AL_LOGIN_SYN()
	{
		memset( this, 0, sizeof(MSG_AL_LOGIN_SYN) );
		
		m_byCategory = AL_ClientLogin;
		m_byProtocol = AL_Login_SYN;
	}
};

struct MSG_AL_LOGIN_ANC : public MSG_BASE_FORWARD
{
	unsigned int uiRootID;
	
	MSG_AL_LOGIN_ANC()
	{
		memset( this, 0, sizeof(MSG_AL_LOGIN_ANC) );
		
		m_byCategory = AL_ClientLogin;
		m_byProtocol = AL_Login_SYN;
	}
};


struct MSG_AL_LOGOUT_SYN : public MSG_BASE_FORWARD
{
	unsigned int uiRootID;
	
	MSG_AL_LOGOUT_SYN()
	{
		memset( this, 0, sizeof(MSG_AL_LOGOUT_SYN) );
		
		m_byCategory = AL_ClientLogin;
		m_byProtocol = AL_Logout_SYN;
	}
};


#pragma pack(pop)

#endif // _PACKAGESTRUCT_CA_H_
