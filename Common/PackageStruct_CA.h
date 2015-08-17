#ifndef _PACKAGESTRUCT_CA_H_INCLUDED_
#define _PACKAGESTRUCT_CA_H_INCLUDED_

#include "PackageStruct.h"
#include "Protocol_CA.h"
#include "Define.h"

#pragma pack(push, 1)

struct MSG_LOGIN : public MSG_BASE
{
	char 	m_szBuffer[512];
};

struct MSG_CA_CONNECTION_ENTERSERVER_SYN : public MSG_BASE
{
	DWORD   m_dwUserID;
	DWORD   m_dwCode;
	//BYTE	m_byTicket[TICKET_LEN];	
	
	MSG_CA_CONNECTION_ENTERSERVER_SYN() 
	{
		memset( this, 0, sizeof(MSG_CA_CONNECTION_ENTERSERVER_SYN) );
		
		m_byCategory = CA_Connect;
		m_byProtocol = CA_Login_REQ;
	}
};

struct MSG_CA_CONNECTION_ENTERSERVER_NAK : public MSG_BASE
{
	DWORD   m_dwErrorCode;
	
	MSG_CA_CONNECTION_ENTERSERVER_NAK() 
	{
		memset( this, 0, sizeof(MSG_CA_CONNECTION_ENTERSERVER_NAK) );
		
		m_byCategory = CA_Connect;
		m_byProtocol = CA_Login_NAK;
	}
};

struct MSG_CA_CONNECTION_ENTERSERVER_ANC : public MSG_BASE
{	
	DWORD   m_dwUserID;
	//BYTE	m_byTicket[TICKET_LEN];
	
	MSG_CA_CONNECTION_ENTERSERVER_ANC() 
	{
		memset( this, 0, sizeof(MSG_CA_CONNECTION_ENTERSERVER_ANC) );
		
		m_byCategory = CA_Connect;
		m_byProtocol = CA_Login_ANC;
	}
};

// 开始游戏 请求
struct MSG_CA_START_GAME_REQ : public MSG_BASE_FORWARD
{
	DWORD 	m_dwUserID;
	
	MSG_CA_START_GAME_REQ() 
	{
		memset( this, 0, sizeof(MSG_CA_START_GAME_REQ) );
		
		m_byCategory = CA_Game; // 32
		m_byProtocol = CA_StartGame_REQ; // 301
	}
};

// 加入房间 请求
struct MSG_CA_JOINROOM_REQ : public MSG_BASE_FORWARD
{
	DWORD 	m_dwUserID;
	BYTE m_byRoomNumber;
	
	MSG_CA_JOINROOM_REQ() 
	{
		memset( this, 0, sizeof(MSG_CA_JOINROOM_REQ) );
		
		m_byCategory = CA_Game; // 32
		m_byProtocol = CA_JoinRoom_REQ; // 303
	}
};

// 加入桌子 请求
struct MSG_CA_JOINTABLE_REQ : public MSG_BASE_FORWARD
{
	DWORD 	m_dwUserID;
	BYTE m_byTableNumber;
	
	MSG_CA_JOINTABLE_REQ() 
	{
		memset( this, 0, sizeof(MSG_CA_JOINTABLE_REQ) );
		
		m_byCategory = CA_Game; // 32
		m_byProtocol = CA_JoinTable_REQ; // 305
	}
};


#pragma pack(pop)

#endif // _PACKAGESTRUCT_CA_H_
