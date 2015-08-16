#ifndef _PACKAGESTRUCT_GA_H_INCLUDED_
#define _PACKAGESTRUCT_GA_H_INCLUDED_

#include "PackageStruct.h"
#include "Protocol_GA.h"
#include "Define.h"

#pragma pack(push, 1)

struct MSG_AG_START_GAME_REQ : public MSG_BASE
{
	DWORD   m_dwUserKey;
	//DWORD   m_dwCode;
	//BYTE	m_byTicket[TICKET_LEN];	
	
	MSG_AG_START_GAME_REQ() 
	{
		memset( this, 0, sizeof(MSG_AG_START_GAME_REQ) );
		
		m_byCategory = AG_Connect; // 40
		m_byProtocol = AG_StartGame_REQ; // 2000
	}
};

struct MSG_AG_START_GAME_ANC : public MSG_BASE
{
	DWORD   m_dwUserKey;
	DWORD   m_dwCode;
	//BYTE	m_byTicket[TICKET_LEN];	
	
	MSG_AG_START_GAME_ANC() 
	{
		memset( this, 0, sizeof(MSG_AG_START_GAME_ANC) );
		
		m_dwCode = 0; // Success 0; Fail 1
		m_byCategory = AG_Connect; // 40
		m_byProtocol = AG_StartGame_ANC; // 2001
	}
};

struct MSG_AG_JOINROOM_REQ : public MSG_FORWARD
{
	BYTE byRoomNumber;
	MSG_AG_JOINROOM_REQ() 
	{
		memset( this, 0, sizeof(MSG_AG_JOINROOM_REQ) );
		
		m_byCategory = AG_Connect; // 40
		m_byProtocol = AG_JoinRoom_REQ; // 2000
	}
};

struct MSG_AG_JOINROOM_ANC : public MSG_FORWARD
{
	BYTE byRoomNumber;
	MSG_AG_JOINROOM_ANC() 
	{
		memset( this, 0, sizeof(MSG_AG_JOINROOM_ANC) );
		
		m_byCategory = GA_Connect; // 40
		m_byProtocol = GA_JoinRoom_ANC; // 2000
	}
};

struct MSG_AG_JOINTABLE_REQ : public MSG_FORWARD
{
	BYTE byTableNumber;
	MSG_AG_JOINTABLE_REQ() 
	{
		memset( this, 0, sizeof(MSG_AG_JOINTABLE_REQ) );
		
		m_byCategory = GA_Connect; // 40
		m_byProtocol = GA_JoinTable_REQ; // 2000
	}
};

struct MSG_AG_JOINTABLE_ANC : public MSG_FORWARD
{
	BYTE byTableNumber;
	MSG_AG_JOINTABLE_ANC() 
	{
		memset( this, 0, sizeof(MSG_AG_JOINTABLE_ANC) );
		
		m_byCategory = GA_Connect; // 40
		m_byProtocol = GA_JoinTable_ANC; // 2000
	}
};

struct MSG_AG_JOINTABLE_ANC : public MSG_FORWARD
{
	BYTE byTableNumber;
	MSG_AG_JOINTABLE_ANC() 
	{
		memset( this, 0, sizeof(MSG_AG_JOINTABLE_ANC) );
		
		m_byCategory = GA_Connect; // 40
		m_byProtocol = GA_JoinTable_ANC; // 2000
	}
};

#pragma pack(pop)

#endif // _PACKAGESTRUCT_GA_H_INCLUDED_
