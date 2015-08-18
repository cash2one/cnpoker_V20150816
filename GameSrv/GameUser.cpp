#include "GameUser.h"

//#include <ctime>
//#include <cstdlib>

#include "GameServer.h"
#include "GameUserManager.h"

TableInfo GameUser::m_TableInfo[1000] = { TableInfo() };


//TableInfo GameUser::m_TableInfo[] = {
//	{0, "A", "A", 100},
//	{1, "B", "B", 100},
//	{2, "C", "C", 100},
//	{3, "D", "D", 100},
//	{4, "E", "E", 100}
//};

GameUser::GameUser()
{
	m_dwUserKey = 0;
	m_uiRoomNumber = 0;
	m_uiTableNumber = 0;
	
	m_uiSeat = 0;
	
	m_uiCardsCount = 0;
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
	DWORD dwUserID = GameUser::m_TableInfo[m_uiTableNumber].m_uiUserKey[idx];
	GameUser * pUser = g_GameUserManager.Find(dwUserID);
	if ( pUser != NULL ) {
		return pUser;
	}
	return NULL;
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
	
	BYTE * pMove = GameUser::m_TableInfo[m_uiTableNumber].m_bAllCards;
	pMove[vecCards[0]] = CNPOKER_HOLE; // m_bAllCards[4] = 3
	pMove[vecCards[1]] = CNPOKER_HOLE; // m_bAllCards[51] = 3
	pMove[vecCards[2]] = CNPOKER_HOLE; // m_bAllCards[11] = 3
	
	// 把牌分成3份。但具体是什么牌并不知道
	for(BYTE i=3; i<54; ++i) {
		pMove[ vecCards[i] ] = i%3; // m_bAllCards[15] = 0; m_bAllCards[24] = 1; m_bAllCards[35] = 2; // 第15张是玩家0的牌,24张是玩家1的牌...
	}
}

void GameUser::AllocCards()
{
	vector<BYTE> vecCards;
	for(BYTE i=0; i<54; ++i) {
		vecCards.push_back(i);
	}	
	random_shuffle( vecCards.begin(), vecCards.end() ); // 乱序
	
	BYTE * pMove = GameUser::m_TableInfo[m_uiTableNumber].m_bAllCards;
	
	BYTE * pCards = m_byCards;
	for(BYTE i=3; i<54; ++i) {
		BYTE bySeat = pMove[i];
		if (m_uiSeat == bySeat)
		{
			*pCards = vecCards[i];
			pCards++;
			
			m_uiCardsCount++; // 记录一共有多少张牌
		}	
	}
	
#if 0	
	// 把另外2份牌发送给其他2个User
	GameUser * pFirst = pUser;
	for(int i=0; i<2; ++i) {
		GameUser * pNextUser = pFirst->GetNextGameUser();
		pNextUser->AllocCards(); // 把牌分给对应的人。 牌出来了。
		pFirst = pNextUser;	
	}
#endif	
	
	//GetNext
	//->AllocCards();
}

void GameUser::ShowCards()
{
	printf("[ShowCards] : Table Number = %d\n", m_uiTableNumber);	
	
	MSG_AG_SHOWCARDS_ANC msg2;
	msg2.m_dwUserKey = m_dwUserKey;
	memcpy(msg2.m_byCards, m_byCards, CNPOKER_CARD_LEN_2); // 将明牌玩家的牌复制进消息包中

	// 发送给另外一个玩家
	unsigned int idx = (m_uiSeat + 1) % 3;
	DWORD dwOtherUserID = GameUser::m_TableInfo[m_uiTableNumber].m_uiUserKey[idx];
	msg2.m_byParameter = dwOtherUserID;
	g_GameServer->SendToAgentServer( (BYTE *)&msg2, sizeof(msg2) );
	
	// 再发送给另外一个玩家
	idx = (idx + 1) % 3;
	dwOtherUserID = GameUser::m_TableInfo[m_uiTableNumber].m_uiUserKey[idx];
	msg2.m_byParameter = dwOtherUserID;
	g_GameServer->SendToAgentServer( (BYTE *)&msg2, sizeof(msg2) );	
}

void GameUser::Discards(BYTE * pCards, unsigned int uiSize)
{
	printf("[Discards] : Table Number = %d\n", m_uiTableNumber);	

	// 找出打出的牌，m_bDiscards数组对应位置 置1
	FigureOutDiscards(pCards, uiSize); // 传入 玩家打出的牌数组 和 个数

	MSG_AG_DISCARDS_ANC msg2;
	msg2.m_dwParameter = m_dwUserKey;
	msg2.m_uiSize = uiSize;
	memcpy(msg2.m_byDiscards, pCards, uiSize);
	
	// 发送给另外一个玩家
	unsigned int idx = (m_uiSeat + 1) % 3;
	DWORD dwOtherUserID = GameUser::m_TableInfo[m_uiTableNumber].m_uiUserKey[idx];
	msg2.m_byParameter = dwOtherUserID;
	g_GameServer->SendToAgentServer( (BYTE *)&msg2, sizeof(msg2) );
	
	// 再发送给另外一个玩家
	idx = (idx + 1) % 3;
	dwOtherUserID = GameUser::m_TableInfo[m_uiTableNumber].m_uiUserKey[idx];
	msg2.m_byParameter = dwOtherUserID;
	g_GameServer->SendToAgentServer( (BYTE *)&msg2, sizeof(msg2) );
}

BOOL GameUser::IsWinTheGame()
{
	if ( m_uiCardsCount == 0)
	{
		return TRUE;
	}
	return FALSE;
}

void GameUser::Broadcast(BYTE *pMsg, WORD wSize)
{	
	#if 0
	for ()
	{
		userkey= 	GameUser::m_TableInfo[m_uiTableNumber ].m_szUserKey[i];
		if user ！= m_dwUserKey
		{
			send()
		}
	}
	#endif
}

void GameUser::FigureOutDiscards(BYTE * pCards, unsigned int uiSize) // 出的牌 3,4,5 --> 3张
{
	if ( (m_uiTableNumber > 0) && (m_uiTableNumber < 1000) )
	{
		for(int i=0; i<uiSize; ++i)
		{
			for(int j=0; j<m_uiCardsCount; ++j) // 手上的牌
			{			
				if ( m_byCards[j] == pCards[i] )
				{	
					if ( GameUser::m_TableInfo[m_uiTableNumber].m_bDiscards[*pCards] == 1 )
					{
						printf("Error: Cheat\n");
						return;
					}
					GameUser::m_TableInfo[m_uiTableNumber].m_bDiscards[*pCards] = 1;
					m_uiCardsCount--; // 手上牌数量减少
					
				}
			}
		}
		// 这里少了个步骤，将手上的牌重新赋值
	}
	else
	{
		printf("Error: Table Number is not correct.\n");
	}
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

