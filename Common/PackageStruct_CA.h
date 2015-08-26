#ifndef _PACKAGESTRUCT_CA_H_INCLUDED_
#define _PACKAGESTRUCT_CA_H_INCLUDED_

#include "PackageStruct.h"
#include "Protocol_CA.h"

#include "CommStruct.h"

#pragma pack(push, 1)

struct MSG_CA_CONNECTION_ENTERSERVER_SYN : public MSG_BASE_FORWARD
{
	DWORD 	m_uiRootID;
	BYTE 	m_byUserKey[CODE_KEY_LEN + 1];
	
	MSG_CA_CONNECTION_ENTERSERVER_SYN() 
	{
		memset( this, 0, sizeof(MSG_CA_CONNECTION_ENTERSERVER_SYN) );
		
		m_byCategory = CA_Connect;
		m_byProtocol = CA_Login_REQ;
		
		m_dwParameter = 0; // dwUserID
		m_byParameter = 0;
	}
};

struct MSG_CA_CONNECTION_ENTERSERVER_NAK : public MSG_BASE_FORWARD
{
	DWORD   m_dwErrorCode;
	
	MSG_CA_CONNECTION_ENTERSERVER_NAK() 
	{
		memset( this, 0, sizeof(MSG_CA_CONNECTION_ENTERSERVER_NAK) );
		
		m_byCategory = CA_Connect;
		m_byProtocol = CA_Login_NAK;
		
		m_dwParameter = 0; // dwUserID
		m_byParameter = 0;
	}
};

struct MSG_CA_CONNECTION_ENTERSERVER_ANC : public MSG_BASE_FORWARD
{	
	//DWORD   m_dwUserID;
	//BYTE	m_byTicket[TICKET_LEN];
	
	MSG_CA_CONNECTION_ENTERSERVER_ANC() 
	{
		memset( this, 0, sizeof(MSG_CA_CONNECTION_ENTERSERVER_ANC) );
		
		m_byCategory = CA_Connect;
		m_byProtocol = CA_Login_ANC;
		
		m_dwParameter = 0; // dwUserID
		m_byParameter = 0;
	}
};

// 预登陆 请求
struct MSG_CA_PRELOGIN_REQ : public MSG_BASE_FORWARD
{
	BYTE 	m_byUsername[32];
	BYTE 	m_byPassword[32];
	
	MSG_CA_PRELOGIN_REQ() 
	{
		memset( this, 0, sizeof(MSG_CA_PRELOGIN_REQ) );
		
		m_byCategory = CA_Client; // 
		m_byProtocol = CA_PreLogin_REQ; // 
		
		m_dwParameter = 0; // dwUserID
		m_byParameter = 0;
	}
};


// 预登陆 应答
struct MSG_CA_PRELOGIN_ANC : public MSG_BASE_FORWARD
{
	DWORD 	m_uiRootID;
	BYTE 	m_byUserKey[CODE_KEY_LEN + 1];
	
	BYTE	m_byIP[IP_MAX_LEN]; // 32
	DWORD	m_dwPort;
	
	MSG_CA_PRELOGIN_ANC() 
	{
		memset( this, 0, sizeof(MSG_CA_PRELOGIN_ANC) );
		
		m_byCategory = CA_Client; // 32
		m_byProtocol = CA_PreLogin_ANC; // 
		
		m_dwParameter = 0; // dwUserID
		m_byParameter = 0;
	}
};

// 登陆 请求
struct MSG_CA_LOGIN_REQ : public MSG_BASE_FORWARD
{
	DWORD	m_uiRootID;
	BYTE 	m_byUserKey[CODE_KEY_LEN + 1];
	
	MSG_CA_LOGIN_REQ() 
	{
		memset( this, 0, sizeof(MSG_CA_LOGIN_REQ) );
		
		m_byCategory = CA_Client; // 32
		m_byProtocol = CA_Login_REQ; // ???
		
		m_dwParameter = 0; // dwUserID
		m_byParameter = 0;
	}
};

// 登陆 应答
struct MSG_CA_LOGIN_ANC : public MSG_BASE_FORWARD
{
	PlayerInfo m_playerInfo;
	//DWORD	m_uiRootID;
	//BYTE 	m_byUserKey[CODE_KEY_LEN + 1];
	
	MSG_CA_LOGIN_ANC() 
	{
		memset( this, 0, sizeof(MSG_CA_LOGIN_ANC) );
		
		m_byCategory = CA_Client; // 32
		m_byProtocol = CA_Login_ANC; // ???
		
		m_dwParameter = 0; // dwUserID
		m_byParameter = 0;
	}
};

// 登陆 失败
struct MSG_CA_LOGIN_NAK : public MSG_BASE_FORWARD
{
	DWORD 	m_dwErrorCode;
	
	MSG_CA_LOGIN_NAK() 
	{
		memset( this, 0, sizeof(MSG_CA_LOGIN_NAK) );
		
		m_byCategory = CA_Client; // 32
		m_byProtocol = CA_Login_NAK; //
		
		m_dwParameter = 0; // dwUserID
		m_byParameter = 0;
	}
};

// 登出 请求
struct MSG_CA_LOGOUT_REQ : public MSG_BASE_FORWARD
{
	DWORD	m_uiRootID;
	
	MSG_CA_LOGOUT_REQ() 
	{
		memset( this, 0, sizeof(MSG_CA_LOGOUT_REQ) );
		
		m_byCategory = CA_Client; // 32
		m_byProtocol = CA_Logout_REQ; // ???
		
		m_dwParameter = 0; // dwUserID
		m_byParameter = 0;
	}
};

// 登出 应答
struct MSG_CA_LOGOUT_ANC : public MSG_BASE_FORWARD
{
	//DWORD	m_uiRootID;
	
	MSG_CA_LOGOUT_ANC() 
	{
		memset( this, 0, sizeof(MSG_CA_LOGOUT_ANC) );
		
		m_byCategory = CA_Client; // 32
		m_byProtocol = CA_Logout_ANC; // ???
		
		m_dwParameter = 0; // dwUserID
		m_byParameter = 0;
	}
};


// 开始游戏 请求
struct MSG_CA_START_GAME_REQ : public MSG_BASE_FORWARD
{
	//DWORD 	m_dwUserID;
	
	MSG_CA_START_GAME_REQ() 
	{
		memset( this, 0, sizeof(MSG_CA_START_GAME_REQ) );
		
		m_byCategory = CA_Game; // 32
		m_byProtocol = CA_StartGame_REQ; // 301
		
		m_dwParameter = 0; // dwUserID
		m_byParameter = 0;
	}
};

// 加入房间 请求
struct MSG_CA_JOINROOM_REQ : public MSG_BASE_FORWARD
{
	//DWORD 	m_dwUserID;
	unsigned int m_uiRoomNumber;
	
	MSG_CA_JOINROOM_REQ() 
	{
		memset( this, 0, sizeof(MSG_CA_JOINROOM_REQ) );
		
		m_byCategory = CA_Game; // 32
		m_byProtocol = CA_JoinRoom_REQ; // 303
		
		m_dwParameter = 0; // dwUserID
		m_byParameter = 0;
	}
};

// 加入桌子 请求
struct MSG_CA_JOINTABLE_REQ : public MSG_BASE_FORWARD
{
	//DWORD 	m_dwUserID;
	unsigned int m_uiTableNumber;
	
	MSG_CA_JOINTABLE_REQ() 
	{
		memset( this, 0, sizeof(MSG_CA_JOINTABLE_REQ) );
		
		m_byCategory = CA_Game; // 32
		m_byProtocol = CA_JoinTable_REQ; // 305
		
		m_dwParameter = 0; // dwUserID
		m_byParameter = 0;
	}
};


#pragma pack(pop)

#endif // _PACKAGESTRUCT_CA_H_
