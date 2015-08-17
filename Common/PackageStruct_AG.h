#ifndef _PACKAGESTRUCT_GA_H_INCLUDED_
#define _PACKAGESTRUCT_GA_H_INCLUDED_

#include "PackageStruct.h"
#include "Protocol_AG.h"
#include "Define.h"

#pragma pack(push, 1)

struct MSG_AG_START_GAME_REQ : public MSG_BASE
{
	DWORD   m_dwUserKey;
	
	MSG_AG_START_GAME_REQ() 
	{
		memset( this, 0, sizeof(MSG_AG_START_GAME_REQ) );
		
		m_byCategory = AG_Connect; // 10
		m_byProtocol = AG_StartGame_REQ; // 2000
	}
};

struct MSG_AG_START_GAME_ANC : public MSG_BASE
{
	DWORD   m_dwUserKey;
	
	MSG_AG_START_GAME_ANC() 
	{
		memset( this, 0, sizeof(MSG_AG_START_GAME_ANC) );
		
		m_byCategory = AG_Connect; // 10
		m_byProtocol = AG_StartGame_ANC; // 2001
	}
};

struct MSG_AG_JOINROOM_REQ : public MSG_BASE_FORWARD // MSG_BASE_FORWARD
{
	DWORD   m_dwUserKey;
	BYTE m_byRoomNumber;
	
	MSG_AG_JOINROOM_REQ() 
	{
		memset( this, 0, sizeof(MSG_AG_JOINROOM_REQ) );
		
		m_byCategory = AG_Connect; // 10
		m_byProtocol = AG_JoinRoom_REQ; // 2002
	}
};

struct MSG_AG_JOINROOM_ANC : public MSG_BASE_FORWARD // MSG_BASE_FORWARD
{
	BYTE m_byRoomNumber;
	
	MSG_AG_JOINROOM_ANC() 
	{
		memset( this, 0, sizeof(MSG_AG_JOINROOM_ANC) );
		
		m_byCategory = AG_Connect; // 10
		m_byProtocol = AG_JoinRoom_ANC; // 2003
	}
};

struct MSG_AG_JOINTABLE_REQ : public MSG_BASE_FORWARD // MSG_BASE_FORWARD
{
	DWORD   m_dwUserKey;
	BYTE m_byTableNumber;
	
	MSG_AG_JOINTABLE_REQ() 
	{
		memset( this, 0, sizeof(MSG_AG_JOINTABLE_REQ) );
		
		m_byCategory = AG_Connect; // 10
		m_byProtocol = AG_JoinTable_REQ; // 2004
	}
};

struct MSG_AG_JOINTABLE_ANC : public MSG_BASE_FORWARD // MSG_BASE_FORWARD
{
	BYTE m_byTableNumber;
	
	MSG_AG_JOINTABLE_ANC() 
	{
		memset( this, 0, sizeof(MSG_AG_JOINTABLE_ANC) );
		
		m_byCategory = AG_Connect; // 10
		m_byProtocol = AG_JoinTable_ANC; // 2005
	}
};


#pragma pack(pop)

#endif // _PACKAGESTRUCT_GA_H_INCLUDED_
