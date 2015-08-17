#ifndef _COMMSTRUCT_H_INCLUDED_
#define _COMMSTRUCT_H_INCLUDED_

#include "Common.h"

struct PlayerInfo 
{
	DWORD m_dwUserKey; 		// 用户的Key
	uint m_uiDBUserID; 		// 用户数据库ID
	uint m_uiMoney; 		// 拥有的钱
	uint m_uiPrepaid; 		// 预付的钱

	uint m_uiRankList; 		// 排行
	uint m_uiGoodsList[5]; 	// 道具
	
	float m_fWonRate; 		// 胜率
	float m_fEscapeRate; 	// 逃跑率
	
	PlayerInfo()
	{
		memset( this, 0, sizeof(PlayerInfo) );
	}
};

/*	struct CardInfo
{
	uint m_uiCards[CNPOKER_CARD_LEN_2]; 	// 握有的牌
	bool m_bDiscards[CNPOKER_CARD_LEN_1]; 	// 打出的牌
	
	CardInfo()
	{
		memset( this, 0, sizeof(Cards) );		
	}
};	*/

struct TableInfo 
{
	//map<DWORD, DWORD> m_mapUserSeat; // UserKey -> 
	uint m_szUserKey[3]; 	// 玩家{1,2,3} - Key
	uint m_szUserWons[3]; 	// 玩家{1,2,3} - 胜率
	uint m_szUserMoney[3]; 	// 玩家{1,2,3} - 钱池
	
	BYTE m_bAllCards[CNPOKER_CARD_LEN_1]; 	// 初始的牌	// m_bAllCards[0] = 0,1,2,3 
	BYTE m_bDiscards[CNPOKER_CARD_LEN_1]; 	// 打出的牌	// m_bDiscards[0] = 0,1
	
	TableInfo()
	{
		memset( this, 0, sizeof(TableInfo) );
	}
};

struct GameInfo
{
	unsigned int uiRootID;
	unsigned int uiScore;
	unsigned int uiFaileds;
	unsigned int uiWons;
	unsigned int uiEscape;
	
	GameInfo()
	{
		memset( this, 0, sizeof(GameInfo) );
	}
};


#endif // _COMMSTRUCT_H_INCLUDED_
