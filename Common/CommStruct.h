#ifndef _COMMSTRUCT_H_INCLUDED_
#define _COMMSTRUCT_H_INCLUDED_

#include "Common.h"
//#include "GameUser.h"

struct PlayerInfo 
{
	DWORD m_dwUserKey; 		// 用户的Key
	uint m_uiDBUserID; 		// 用户数据库ID
	uint m_uiMoney; 		// 拥有的钱
	uint m_uiPrepaid; 		// 预付的钱
	
	uint m_uiFaileds; 		// 失败次数
	uint m_uiWons; 			// 赢的次数
	uint m_uiEscape; 		// 逃跑次数
	uint m_uiScore; 		// 分数
	
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
	//map<uint, GameUser *> m_mapSeatGameUser; // 通过位置 查找 GameUser
	
	uint m_uiUserKey[3]; 	// 玩家{1,2,3} - Key
	uint m_uiUserWons[3]; 	// 玩家{1,2,3} - 胜率
	uint m_uiUserMoney[3]; 	// 玩家{1,2,3} - 钱池
	
	BYTE m_byExtraCards[3]; // 抢地主额外的三张牌
	BYTE m_byAllCards[CNPOKER_CARD_LEN_1]; 	// 初始的牌 54张 // m_bAllCards[0] = 0,1,2,3,...53
	char m_byDiscards[CNPOKER_CARD_LEN_1]; 	// 打出的牌	// m_bDiscards[0] = 0,-1; 0 未出的牌; -1 已出的牌
		
	uint m_uiLastMsg; // 最后一个有牌权的人
	uint m_uiLastDis; // 上一个出牌的人
	
	BYTE m_byCmpValue; // 比较的值
	BYTE m_byCmpCount; // 比较的值 的 个数
	
	BYTE m_byCallLandlord; // 叫地主
	unsigned int m_uiGrabTimes; // 抢地主次数
	
	TableInfo()
	{
		m_uiLastDis = -1;
		m_uiLastMsg = -1;
		
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
