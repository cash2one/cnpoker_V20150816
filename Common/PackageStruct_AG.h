#ifndef _PACKAGESTRUCT_GA_H_INCLUDED_
#define _PACKAGESTRUCT_GA_H_INCLUDED_

#include "PackageStruct.h"
#include "Protocol_AG.h"

#include "CommStruct.h"

#pragma pack(push, 1)

// 登录 请求
struct MSG_AG_LOGIN_REQ : public MSG_BASE_FORWARD
{
	DWORD m_uiRootID;
	
	MSG_AG_LOGIN_REQ() 
	{
		memset( this, 0, sizeof(MSG_AG_LOGIN_REQ) );
		
		m_byCategory = AG_Connect; // 10
		m_byProtocol = AG_Login_REQ; // 
		
		m_dwParameter = 0; // dwUserID
		m_byParameter = 0;
	}
};

// 登录 应答
struct MSG_AG_LOGIN_ANC : public MSG_BASE_FORWARD
{
	PlayerInfo m_playerInfo;
	//unsigned int m_uiRootID;
	
	MSG_AG_LOGIN_ANC() 
	{
		memset( this, 0, sizeof(MSG_AG_LOGIN_ANC) );
		
		m_byCategory = AG_Connect; // 10
		m_byProtocol = AG_Login_ANC; //
		
		m_dwParameter = 0; // dwUserID
		m_byParameter = 0;
	}
};

// 登出 请求
struct MSG_AG_LOGOUT_REQ : public MSG_BASE_FORWARD
{
	DWORD m_uiRootID;
	
	MSG_AG_LOGOUT_REQ() 
	{
		memset( this, 0, sizeof(MSG_AG_LOGOUT_REQ) );
		
		m_byCategory = AG_Connect; // 10
		m_byProtocol = AG_Logout_REQ; // 
		
		m_dwParameter = 0; // dwUserID
		m_byParameter = 0;
	}
};

// 登出 应答
struct MSG_AG_LOGOUT_ANC : public MSG_BASE_FORWARD
{
	DWORD m_uiRootID;
	
	MSG_AG_LOGOUT_ANC() 
	{
		memset( this, 0, sizeof(MSG_AG_LOGOUT_ANC) );
		
		m_byCategory = AG_Connect; // 10
		m_byProtocol = AG_Logout_ANC; // 
		
		m_dwParameter = 0; // dwUserID
		m_byParameter = 0;
	}
};

struct MSG_AG_START_GAME_REQ : public MSG_BASE_FORWARD
{
	MSG_AG_START_GAME_REQ() 
	{
		memset( this, 0, sizeof(MSG_AG_START_GAME_REQ) );
		
		m_byCategory = AG_Connect; // 10
		m_byProtocol = AG_StartGame_REQ; // 2000
		
		m_dwParameter = 0; // dwUserID
		m_byParameter = 0;
	}
};

struct MSG_AG_START_GAME_ANC : public MSG_BASE_FORWARD
{
	MSG_AG_START_GAME_ANC() 
	{
		memset( this, 0, sizeof(MSG_AG_START_GAME_ANC) );
		
		m_byCategory = AG_Connect; // 10
		m_byProtocol = AG_StartGame_ANC; // 2001
		
		m_dwParameter = 0; // dwUserID
		m_byParameter = 0;
	}
};

struct MSG_AG_START_GAME_NAK : public MSG_BASE_FORWARD
{
	DWORD 	m_dwErrorCode;
	
	MSG_AG_START_GAME_NAK() 
	{
		memset( this, 0, sizeof(MSG_AG_START_GAME_NAK) );
		
		m_byCategory = AG_Connect; // 10
		//m_byProtocol = AG_StartGame_NAK; // ???
		
		m_dwParameter = 0; // dwUserID
		m_byParameter = 0;
	}
};

struct MSG_AG_JOINROOM_REQ : public MSG_BASE_FORWARD
{
	unsigned int m_uiRoomNumber;
	
	MSG_AG_JOINROOM_REQ() 
	{
		memset( this, 0, sizeof(MSG_AG_JOINROOM_REQ) );
		
		m_byCategory = AG_Connect; // 10
		m_byProtocol = AG_JoinRoom_REQ; // 2002
		
		m_dwParameter = 0; // dwUserID
		m_byParameter = 0;
	}
};

struct MSG_AG_JOINROOM_ANC : public MSG_BASE_FORWARD
{
	//PlayerInfo m_playerInfo;
	//unsigned int m_byRoomNumber;
	
	MSG_AG_JOINROOM_ANC() 
	{
		memset( this, 0, sizeof(MSG_AG_JOINROOM_ANC) );
		
		m_byCategory = AG_Connect; // 10
		m_byProtocol = AG_JoinRoom_ANC; // 2003
		
		m_dwParameter = 0; // dwUserID
		m_byParameter = 0;
	}
};

struct MSG_AG_JOINTABLE_REQ : public MSG_BASE_FORWARD
{
	unsigned int m_uiTableNumber;
	//unsigned int m_uiSeat;
	
	MSG_AG_JOINTABLE_REQ() 
	{
		memset( this, 0, sizeof(MSG_AG_JOINTABLE_REQ) );
		
		m_byCategory = AG_Connect; // 10
		m_byProtocol = AG_JoinTable_REQ; // 2004
		
		m_dwParameter = 0; // dwUserID
		m_byParameter = 0;
	}
};

struct MSG_AG_JOINTABLE_ANC : public MSG_BASE_FORWARD
{
	unsigned int m_uiTableNumber;
	
	MSG_AG_JOINTABLE_ANC() 
	{
		memset( this, 0, sizeof(MSG_AG_JOINTABLE_ANC) );
		
		m_byCategory = AG_Connect; // 10
		m_byProtocol = AG_JoinTable_ANC; // 2005
		
		m_dwParameter = 0; // dwUserID
		m_byParameter = 0;
	}
};

// 初始化牌
struct MSG_AG_INITCARDS_BRD : public MSG_BASE_FORWARD
{
	BYTE m_byCards[20];
	
	MSG_AG_INITCARDS_BRD() 
	{
		memset( this, 0, sizeof(MSG_AG_INITCARDS_BRD) );
		
		m_byCategory = AG_Connect; // 10
		m_byProtocol = AG_InitCards_BRD; // ???
		
		m_dwParameter = 0; // dwUserID
		m_byParameter = 0;
	}
};

struct MSG_AG_INITCARDS_ANC : public MSG_BASE_FORWARD
{
	MSG_AG_INITCARDS_ANC() 
	{
		memset( this, 0, sizeof(MSG_AG_INITCARDS_ANC) );
		
		m_byCategory = AG_Connect; // 10
		//m_byProtocol = AG_InitCards_ANC; // ???
		
		m_dwParameter = 0; // dwUserID
		m_byParameter = 0;
	}
};

// 叫地主 请求
struct MSG_AG_CALLLANDLOARD_REQ : public MSG_BASE_FORWARD
{
	BYTE m_byCall; // 0 不叫， 1 叫地主
	
	MSG_AG_CALLLANDLOARD_REQ()
	{
		memset( this, 0, sizeof(MSG_AG_CALLLANDLOARD_REQ) );
		
		m_byCategory = AG_Connect; // 10
		m_byProtocol = AG_CallLandlord_REQ; // 
		
		m_dwParameter = 0; // dwUserID
		m_byParameter = 0;
	}
};

// 叫地主 应答
struct MSG_AG_CALLLANDLOARD_ANC : public MSG_BASE_FORWARD
{	
	MSG_AG_CALLLANDLOARD_ANC()
	{
		memset( this, 0, sizeof(MSG_AG_CALLLANDLOARD_ANC) );
		
		m_byCategory = AG_Connect; // 10
		m_byProtocol = AG_CallLandlord_ANC; // 
		
		m_dwParameter = 0; // dwUserID
		m_byParameter = 0;
	}
};

// 抢地主 请求
struct MSG_AG_GRABLANDLOARD_REQ : public MSG_BASE_FORWARD
{
	MSG_AG_GRABLANDLOARD_REQ() 
	{
		memset( this, 0, sizeof(MSG_AG_GRABLANDLOARD_REQ) );
		
		m_byCategory = AG_Connect; // 10
		m_byProtocol = AG_GrabLandlord_REQ; // 
		
		m_dwParameter = 0; // dwUserID
		m_byParameter = 0;
	}
};

// 抢地主 应答
struct MSG_AG_GRABLANDLOARD_ANC : public MSG_BASE_FORWARD
{
	//unsigned int m_uiSeat; // 成功抢到地主的玩家Key 还是说 Seat ?
	
	MSG_AG_GRABLANDLOARD_ANC() 
	{
		memset( this, 0, sizeof(MSG_AG_GRABLANDLOARD_ANC) );
		
		m_byCategory = AG_Connect; // 10
		m_byProtocol = AG_GrabLandlord_ANC; // 
		
		m_dwParameter = 0; // dwUserID
		m_byParameter = 0;
	}
};

// 抢地主 广播 (最终地主确定)
struct MSG_AG_GRABLANDLOARD_BRD : public MSG_BASE_FORWARD
{	
	MSG_AG_GRABLANDLOARD_BRD() 
	{
		memset( this, 0, sizeof(MSG_AG_GRABLANDLOARD_BRD) );
		
		m_byCategory = AG_Connect; // 10
		m_byProtocol = AG_GrabLandlord_BRD; // 
		
		m_dwParameter = 0; // dwUserID
		m_byParameter = 0;
	}
};

// 明牌
struct MSG_AG_SHOWCARDS_REQ : public MSG_BASE_FORWARD
{
	MSG_AG_SHOWCARDS_REQ() 
	{
		memset( this, 0, sizeof(MSG_AG_SHOWCARDS_REQ) );
		
		m_byCategory = AG_Connect; // 10
		m_byProtocol = AG_ShowCards_REQ; // ???
		
		m_dwParameter = 0; // dwUserID
		m_byParameter = 0;
	}
};

struct MSG_AG_SHOWCARDS_ANC : public MSG_BASE_FORWARD
{
	DWORD m_dwUserID;
	BYTE  m_byCards[CNPOKER_CARD_LEN_2]; // 20
	
	MSG_AG_SHOWCARDS_ANC() 
	{
		memset( this, 0, sizeof(MSG_AG_SHOWCARDS_ANC) );
		
		m_byCategory = AG_Connect; // 10
		m_byProtocol = AG_ShowCards_ANC; // ???
		
		m_dwParameter = 0; // dwUserID
		m_byParameter = 0;
	}
};

// 出牌
struct MSG_AG_DISCARDS_REQ : public MSG_BASE_FORWARD
{
	unsigned int m_uiSize;
	BYTE m_byDiscards[CNPOKER_CARD_LEN_2]; // 最多20张
	
	MSG_AG_DISCARDS_REQ() 
	{
		memset( this, 0, sizeof(MSG_AG_DISCARDS_REQ) );
		
		m_byCategory = AG_Connect; // 10
		m_byProtocol = AG_Discards_REQ; // ???
		
		m_dwParameter = 0; // dwUserID
		m_byParameter = 0;
	}
};

struct MSG_AG_DISCARDS_ANC : public MSG_BASE_FORWARD
{
	DWORD m_dwUserID;
	DWORD m_uiSize;
	BYTE m_byDiscards[CNPOKER_CARD_LEN_2]; // 最多20张
	
	MSG_AG_DISCARDS_ANC() 
	{
		memset( this, 0, sizeof(MSG_AG_DISCARDS_ANC) );
		
		m_byCategory = AG_Connect; // 10
		m_byProtocol = AG_Discards_ANC; // ???
		
		m_dwParameter = 0; // dwUserID
		m_byParameter = 0;
	}
};

// 出牌 无效 
struct MSG_AG_DISCARDS_INVALID : public MSG_BASE_FORWARD
{
	DWORD m_dwErrorCode;
	
	MSG_AG_DISCARDS_INVALID() 
	{
		memset( this, 0, sizeof(MSG_AG_DISCARDS_INVALID) );
		
		m_byCategory = AG_Connect; // 10
		m_byProtocol = AG_Discards_INVALID; // ???
		
		m_dwParameter = 0; // dwUserID
		m_byParameter = 0;
	}
};

// 要不起 请求
struct MSG_AG_PASS_REQ : public MSG_BASE_FORWARD
{	
	MSG_AG_PASS_REQ() 
	{
		memset( this, 0, sizeof(MSG_AG_PASS_REQ) );
		
		m_byCategory = AG_Connect; // 10
		m_byProtocol = AG_Pass_REQ; // ???
		
		m_dwParameter = 0; // dwUserID
		m_byParameter = 0;
	}
};

// 要不起 应答
struct MSG_AG_PASS_ANC : public MSG_BASE_FORWARD
{
	//DWORD m_dwUserKey;
	//DWORD m_uiSize;
	
	MSG_AG_PASS_ANC() 
	{
		memset( this, 0, sizeof(MSG_AG_PASS_ANC) );
		
		m_byCategory = AG_Connect; // 10
		m_byProtocol = AG_Pass_ANC; // ???
		
		m_dwParameter = 0; // dwUserID
		m_byParameter = 0;
	}
};

// 取得胜利
struct MSG_AG_WINPLAYER_BRD : public MSG_BASE_FORWARD
{	
	MSG_AG_WINPLAYER_BRD() 
	{
		memset( this, 0, sizeof(MSG_AG_WINPLAYER_BRD) );
		
		m_byCategory = AG_Connect; // 10
		m_byProtocol = AG_Discards_REQ; // ???
		
		m_dwParameter = 0; // dwUserID
		m_byParameter = 0;
	}
};


#pragma pack(pop)

#endif // _PACKAGESTRUCT_GA_H_INCLUDED_
