#ifndef _PACKAGESTRUCT_CA_H_INCLUDED_
#define _PACKAGESTRUCT_CA_H_INCLUDED_

#include "PackageStruct.h"
#include "Protocol_CA.h"

#pragma pack(push, 1)


struct MSG_CA_CONNECTION_ENTERSERVER_SYN : public MSG_BASE_FORWARD
{
	//DWORD   m_dwUserID;
	
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

// 登陆游戏 请求
struct MSG_CA_PRELOGIN_GAME_REQ : public MSG_BASE_FORWARD
{
	BYTE byUsername[32];
	BYTE byPassword[32];
	
	MSG_CA_PRELOGIN_GAME_REQ() 
	{
		memset( this, 0, sizeof(MSG_CA_PRELOGIN_GAME_REQ) );
		
		m_byCategory = CA_Game; // 32
		m_byProtocol = CA_Prelogin_REQ; // ???
		
		m_dwParameter = 0; // dwUserID
		m_byParameter = 0;
	}
};


// 登陆游戏 请求
struct MSG_CA_PRELOGIN_GAME_ANC : public MSG_BASE_FORWARD
{
	DWORD 	uiRootID;
	BYTE 	byUserKey[CODE_KEY_LEN + 1];
	
	BYTE	m_byIP[BYTE_IP_LEN];
	DWORD	m_Port;
	
	MSG_CA_PRELOGIN_GAME_ANC() 
	{
		memset( this, 0, sizeof(MSG_CA_PRELOGIN_GAME_ANC) );
		
		m_byCategory = CA_Game; // 32
		m_byProtocol = CA_Prelogin_ANC; // ???
		
		m_dwParameter = 0; // dwUserID
		m_byParameter = 0;
	}
};

//
struct MSG_CA_LOGIN_GAME_REQ : public MSG_BASE_FORWARD
{
	DWORD	m_uiRootID;
	BYTE 	byUserKey[CODE_KEY_LEN + 1];
	
	MSG_CA_LOGIN_GAME_REQ() 
	{
		memset( this, 0, sizeof(MSG_CA_LOGIN_GAME_REQ) );
		
		m_byCategory = CA_Game; // 32
		m_byProtocol = CA_Login_REQ; // ???
		
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
