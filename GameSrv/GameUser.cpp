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
	for(int i=0; i<54; ++i)
	{
		m_vecCards.push_back(i);
	}
	random_shuffle( m_vecCards.begin(), m_vecCards.end() );
	for(int i=0; i<54; ++i)
	{
		printf("%d ", m_vecCards[i]);
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

