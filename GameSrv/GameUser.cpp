#include "GameUser.h"

#include <ctime>
#include <cstdlib>

#include "GameUserManager.h"

//TableInfo GameUser::m_TableInfo[1000] = {0};

GameUser::GameUser()
{
	m_dwUserKey = 0;
	m_uiRoomNumber = 0;
	m_uiTableNumber = 0;
	
	m_uiSeat = 0;
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
	m_pPlayer.m_dwUserKey 	= info.m_dwUserKey; 	// 用户的Key
	m_pPlayer.m_uiDBUserID 	= info.m_uiDBUserID; 	// 用户数据库ID
	m_pPlayer.m_uiFaileds 	= info.m_uiFaileds;
	m_pPlayer.m_uiWons 		= info.m_uiWons;
	m_pPlayer.m_uiEscape 	= info.m_uiEscape;
	m_pPlayer.m_uiScore 	= info.m_uiScore;
		
	//m_pPlayer.m_uiMoney 	= info.m_uiMoney; 		// 拥有的钱
	//m_pPlayer.m_uiPrepaid = info.m_uiPrepaid; 	// 预付的钱
	//float m_fWonRate; 	// 胜率
	//float m_fEscapeRate; 	// 逃跑率
}

GameUser * GameUser::GetNextGameUser()
{
	unsigned int idx = (m_uiSeat + 1) % 3;
	DWORD dwUserID = this->m_TableInfo[m_uiTableNumber].m_uiUserKey[idx];
	GameUser * pUser = g_GameUserManager.Find(dwUserID);
	if ( pUser != NULL ) {
		return pUser;
	}
}

void GameUser::StartGame()
{
	printf("Start Game\n");
}

void GameUser::InitCards()
{
	vector<BYTE> vecCards;
	for(BYTE i=0; i<54; ++i) {
		vecCards.push_back(i);
	}	
	random_shuffle( vecCards.begin(), vecCards.end() ); // 乱序
	
	// 比如说乱序后 vecCards 值为如下:
	// 4 51 11 15 24 35 17 36 26 50 33 39 19 2 47 49 25 18 32 40 5 21 7 12 14 42 27 6 45 44 30 38 13 37 3 16 29 53 9 22 8 23 20 34 1 10 31 0 46 41 48 28 52 43
	
	BYTE * pMove = m_TableInfo[m_uiTableNumber].m_bAllCards;
	pMove[vecCards[0]] = CNPOKER_HOLE; // m_bAllCards[4] = 3
	pMove[vecCards[1]] = CNPOKER_HOLE; // m_bAllCards[51] = 3
	pMove[vecCards[2]] = CNPOKER_HOLE; // m_bAllCards[11] = 3
	
	// 把牌分成3份。但具体是什么牌并不知道
	for(BYTE i=3; i<54; ++i) {
		pMove[ vecCards[i] ] = i%3; // m_bAllCards[15] = 0; m_bAllCards[24] = 1; m_bAllCards[35] = 1; // 第15张是玩家0的牌,24张是玩家1的牌...
	}
}

void GameUser::AllocCards()
{
	vector<BYTE> vecCards;
	for(BYTE i=0; i<54; ++i) {
		vecCards.push_back(i);
	}	
	random_shuffle( vecCards.begin(), vecCards.end() ); // 乱序
	
	BYTE * pMove = m_TableInfo[m_uiTableNumber].m_bAllCards;
	
	BYTE * pCards = m_byCards;
	for(BYTE i=3; i<54; ++i) {
		BYTE bySeat = pMove[i];
		if (m_uiSeat == bySeat)
		{
			*pCards = vecCards[i];
			pCards++;
		}	
	}	
	//GetNext
	//->AllocCards();
}

void GameUser::ShowCards()
{
	
}

void GameUser::Discards()
{
	
}

void GameUser::Broadcast()
{
	#if 0
	for ()
	{
		userkey= 	m_TableInfo[m_uiTableNumber ].m_szUserKey[i];
		if user ！= m_dwUserKey
		{
			send()
		}
	}
	#endif
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

