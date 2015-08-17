#ifndef _PACKAGESTRUCT_GD_H_INCLUDED_
#define _PACKAGESTRUCT_GD_H_INCLUDED_

#include "PackageStruct.h"
#include "Protocol_GD.h"
#include "Define.h"

#pragma pack(push, 1)

struct MSG_GD_LOGIN_SYN : public MSG_BASE_FORWARD
{
	unsigned int uiRootID;
	
	MSG_GD_LOGIN_SYN()
	{
		memset( this, 0, sizeof(MSG_GD_LOGIN_SYN) );
		
		m_byCategory = GD_ClientLogin;
		m_byProtocol = GD_Login_SYN;
				
		m_dwParameter = 0;
		m_byParameter = 0;
	}
};

struct MSG_GD_LOGIN_ANC : public MSG_BASE_FORWARD
{
	unsigned int uiRootID;
	unsigned int uiScore;
	unsigned int uiFaileds;
	unsigned int uiWons;
	unsigned int uiEscape;
		
	MSG_GD_LOGIN_ANC()
	{
		memset( this, 0, sizeof(MSG_GD_LOGIN_ANC) );
		
		m_byCategory = GD_ClientLogin;
		m_byProtocol = GD_Login_ANC;
				
		m_dwParameter = 0;
		m_byParameter = 0;
	}
};

struct MSG_GD_LOGOUT_SYN : public MSG_BASE_FORWARD
{
	MSG_GD_LOGOUT_SYN()
	{
		memset( this, 0, sizeof(MSG_GD_LOGOUT_SYN) );
		
		m_byCategory = GD_ClientLogin;
		m_byProtocol = GD_Logout_SYN;
				
		m_dwParameter = 0;
		m_byParameter = 0;
	}
};


struct MSG_GD_LOGOUT_ANC : public MSG_BASE_FORWARD
{
	MSG_GD_LOGOUT_ANC()
	{
		memset( this, 0, sizeof(MSG_GD_LOGOUT_ANC) );
		
		m_byCategory = GD_ClientLogin;
		m_byProtocol = GD_Logout_ANC;
				
		m_dwParameter = 0;
		m_byParameter = 0;
	}
};

struct MSG_GD_UPDATE_CMD : public MSG_BASE_FORWARD
{
	MSG_GD_UPDATE_CMD()
	{
		memset( this, 0, sizeof(MSG_GD_UPDATE_CMD) );
		
		m_byCategory = GD_ClientLogin;
		m_byProtocol = GD_Update_CMD;
				
		m_dwParameter = 0;
		m_byParameter = 0;
	}
};

struct MSG_GD_UPDATE_ANC : public MSG_BASE_FORWARD
{
	MSG_GD_UPDATE_ANC()
	{
		memset( this, 0, sizeof(MSG_GD_UPDATE_ANC) );
		
		m_byCategory = GD_ClientLogin;
		m_byProtocol = GD_Update_ANC;
				
		m_dwParameter = 0;
		m_byParameter = 0;
	}
};


struct MSG_GD_SAVE_CMD : public MSG_BASE_FORWARD
{
	unsigned int uiRootID;
	unsigned int uiScore;
	unsigned int uiFaileds;
	unsigned int uiWons;
	unsigned int uiEscape;
	
	MSG_GD_SAVE_CMD()
	{
		memset( this, 0, sizeof(MSG_GD_SAVE_CMD) );
		
		m_byCategory = GD_ClientLogin;
		m_byProtocol = GD_Save_CMD;
				
		m_dwParameter = 0;
		m_byParameter = 0;
	}
};

struct MSG_GD_SAVE_ANC : public MSG_BASE_FORWARD
{
	MSG_GD_SAVE_ANC()
	{
		memset( this, 0, sizeof(MSG_GD_SAVE_ANC) );
		
		m_byCategory = GD_ClientLogin;
		m_byProtocol = GD_Save_ANC;
				
		m_dwParameter = 0;
		m_byParameter = 0;
	}
};

#pragma pack(pop)

#endif // _PACKAGESTRUCT_GD_H_INCLUDED_
