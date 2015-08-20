#ifndef _PACKAGESTRUCT_AL_H_INCLUDED_
#define _PACKAGESTRUCT_AL_H_INCLUDED_

#include "PackageStruct.h"
#include "Protocol_AL.h"
#include "Define.h"

#pragma pack(push, 1)

// 预登陆 请求
struct MSG_AL_PRELOGIN_REQ : public MSG_BASE_FORWARD
{
	BYTE m_byUsername[32];
	BYTE m_byPassword[32];
	
	MSG_AL_PRELOGIN_REQ()
	{
		memset( this, 0, sizeof(MSG_AL_PRELOGIN_REQ) );
		
		m_byCategory = LD_ClientLogin;
		m_byProtocol = AL_PreLogin_REQ;
	}
};

// 预登陆 应答
struct MSG_AL_PRELOGIN_ANC : public MSG_BASE_FORWARD
{
	DWORD 	m_uiRootID;
	BYTE 	m_byUserKey[CODE_KEY_LEN + 1];
	
	BYTE	m_byIP[BYTE_IP_LEN];
	DWORD	m_dwPort;
	
	MSG_AL_PRELOGIN_ANC()
	{
		memset( this, 0, sizeof(MSG_AL_PRELOGIN_ANC) );
		
		m_byCategory = AL_ClientLogin;
		m_byProtocol = AL_PreLogin_ANC;
	}
};

// 登陆 请求
struct MSG_AL_LOGIN_REQ : public MSG_BASE_FORWARD
{
	DWORD 	m_uiRootID;
	BYTE 	m_byUserKey[CODE_KEY_LEN + 1];
	
	MSG_AL_LOGIN_REQ()
	{
		memset( this, 0, sizeof(MSG_AL_LOGIN_REQ) );
		
		m_byCategory = AL_ClientLogin;
		m_byProtocol = AL_Login_REQ;
	}
};

// 登陆 应答
struct MSG_AL_LOGIN_ANC : public MSG_BASE_FORWARD
{
	DWORD m_uiRootID;
	
	MSG_AL_LOGIN_ANC()
	{
		memset( this, 0, sizeof(MSG_AL_LOGIN_ANC) );
		
		m_byCategory = AL_ClientLogin;
		m_byProtocol = AL_Login_ANC;
	}
};

// 再次登陆 请求
struct MSG_AL_RELOGIN_REQ : public MSG_BASE_FORWARD
{
	DWORD 	m_uiRootID;
	BYTE 	m_byUserKey[CODE_KEY_LEN + 1];
	
	MSG_AL_RELOGIN_REQ()
	{
		memset( this, 0, sizeof(MSG_AL_RELOGIN_REQ) );
		
		m_byCategory = LD_ClientLogin;
		m_byProtocol = AL_ReLogin_REQ;
	}
};

// 再次登陆 应答
struct MSG_AL_RELOGIN_ANC : public MSG_BASE_FORWARD
{
	DWORD	m_uiRootID;
	BYTE	m_byUserKey[CODE_KEY_LEN + 1];
		
	MSG_AL_RELOGIN_ANC()
	{
		memset( this, 0, sizeof(MSG_AL_RELOGIN_ANC) );
		
		m_byCategory = AL_ClientLogin;
		m_byProtocol = AL_ReLogin_ANC;
	}
};

// 登出 请求
struct MSG_AL_LOGOUT_REQ : public MSG_BASE_FORWARD
{
	DWORD m_uiRootID;
	
	MSG_AL_LOGOUT_REQ()
	{
		memset( this, 0, sizeof(MSG_AL_LOGOUT_REQ) );
		
		m_byCategory = AL_ClientLogin;
		m_byProtocol = AL_Logout_REQ;
	}
};

// 登出 应答
struct MSG_AL_LOGOUT_ANC : public MSG_BASE_FORWARD
{
	MSG_AL_LOGOUT_ANC()
	{
		memset( this, 0, sizeof(MSG_AL_LOGOUT_ANC) );
		
		m_byCategory = AL_ClientLogin;
		m_byProtocol = AL_Logout_ANC;
	}
};


#pragma pack(pop)

#endif // _PACKAGESTRUCT_AL_H_INCLUDED_
