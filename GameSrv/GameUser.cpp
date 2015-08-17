#include "GameUser.h"

#include <ctime>
#include <cstdlib>

GameUser::GameUser()
{
	
}
	
GameUser::~GameUser()
{
	
}

	
void GameUser::LoginRoom(unsigned int _roomid)
{
	
}

void GameUser::logoutRoom()
{
	
}
	
void GameUser::LoginTable(unsigned int _tableid)
{
	
}

void GameUser::logoutTable()
{
	
}
	
	
PlayerInfo & GameUser::GetPlayerInfo()
{
	return m_pPlayer;
}

void GameUser::SetPlayerInfo(PlayerInfo info)
{
	m_pPlayer.m_dwUserKey 	= info.m_dwUserKey; // 用户的Key
	m_pPlayer.m_uiDBUserID 	= info.m_uiDBUserID; // 用户数据库ID
	m_pPlayer.m_uiMoney 	= info.m_uiMoney; // 拥有的钱
	m_pPlayer.m_uiPrepaid 	= info.m_uiPrepaid; // 预付的钱
	
	//float m_fWonRate; 	// 胜率
	//float m_fEscapeRate; 	// 逃跑率
}

void GameUser::StartGame()
{
	printf("Start Game\n");
}

void GameUser::InitCards()
{
	vector<BYTE> m_vecCards;
	for(BYTE i=0; i<54; ++i) {
		m_vecCards.push_back(i);
	}
	
	random_shuffle( m_vecCards.begin(), m_vecCards.end() );
	
	BYTE * pMove = m_TableInfo[m_uiTableNumber].m_bAllCards;
	pMove[m_vecCards[0]] = CNPOKER_HOLE;
	pMove[m_vecCards[1]] = CNPOKER_HOLE;
	pMove[m_vecCards[2]] = CNPOKER_HOLE;
	
	for(BYTE i=3; i<54; ++i) {
		pMove[ m_vecCards[i] ] = i%3;
	}
}

void GameUser::AllocCards()
{
	BYTE * pMove = m_TableInfo[m_uiTableNumber].m_bAllCards;
	
	BYTE * pCards = byCards;
	for(BYTE i=3; i<54; ++i) {
		BYTE bySeat = pMove[i];
		if (m_bySeat == bySeat)
		{
			*pCards = m_vecCards[i];
			pCards++;
		}	
	}
}

void GameUser::ShowCards()
{
	
}

void GameUser::Discards()
{
	
}

//////////////////////////////////////
unsigned short GameUser::GetRandom()
{
	BOOL bRet = is_support_drng();
	if ( bRet ) {
		return GetRandom();
	}
	
	// C++ 随机值
	printf("Don't support DRNG, use C++ srand\n");
	srand( (unsigned)time(0) );
	unsigned short ran_num = rand();
	
	return ran_num;
}

