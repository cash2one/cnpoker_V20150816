#include "GameUser.h"

#include <ctime>
#include <cstdlib>

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

/*******************************/

int myRandom(BYTE i)
{
	return rand() % i;
}


/*******************************/

GameUser::GameUser()
{
	m_dwUserKey = 0;
	m_uiRoomNumber = 0;
	m_uiTableNumber = 0;
	
	m_uiSeat = 0;
	
	m_uiCardsCount = 0;
	
	memset(m_szCards, -1, CNPOKER_CARD_LEN_2);
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
	srand( (unsigned)time(NULL) );
	
	vector<BYTE> vecCards;
	vecCards.reserve(CNPOKER_CARD_LEN_1); // 54
	for(BYTE i=0; i<CNPOKER_CARD_LEN_1; ++i) {
		vecCards.push_back(i);
	}

	std::random_shuffle( vecCards.begin(), vecCards.end(), myRandom ); // 乱序

	// 先全部初始化为 -1
	memset(GameUser::m_TableInfo[m_uiTableNumber].m_bAllCards, -1, CNPOKER_CARD_LEN_1);

	
	BYTE * pMove = GameUser::m_TableInfo[m_uiTableNumber].m_bAllCards;
	pMove[ vecCards[0] ] = CNPOKER_HOLE; // m_bAllCards[4] = 3
	pMove[ vecCards[1] ] = CNPOKER_HOLE; // m_bAllCards[51] = 3
	pMove[ vecCards[2] ] = CNPOKER_HOLE; // m_bAllCards[11] = 3
	
	// 把牌分成3份
	for(BYTE i=0; i<54; ++i) {
		pMove[ vecCards[i] ] = i%3; // 如: m_bAllCards[15] = 0; m_bAllCards[24] = 1; m_bAllCards[35] = 2; // 第15张是玩家0的牌,24张是玩家1的牌...
	}
}

void GameUser::AllocCards()
{	
	BYTE * pMove = GameUser::m_TableInfo[m_uiTableNumber].m_bAllCards;
	
	GameUser * pUser = this;
	for(int i=0; i<3; ++i)
	{
		if (i != 0) // 
		{
			pUser = GetNextGameUser();
		}
		
		char * pUserSelf = pUser->m_szCards;
		for(BYTE i=0; i<CNPOKER_CARD_LEN_1; ++i)
		{
			if ( *pMove == m_uiSeat )
			{
				*pUserSelf++ = i;
				pUser->m_uiCardsCount++;
			}
		}
	}
}

void GameUser::ShowCards()
{
	printf("[ShowCards] : Table Number = %d\n", m_uiTableNumber);	
	
	MSG_AG_SHOWCARDS_ANC msg2;
	msg2.m_dwUserKey = m_dwUserKey;
	memcpy(msg2.m_byCards, m_szCards, CNPOKER_CARD_LEN_2); // 将明牌玩家的牌复制进消息包中

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

	// 找出打出的牌，m_bDiscards， 并检查出牌是否有效
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
	if ( m_uiTableNumber > 1000 ) {
		printf("Error: Table Number is not correct.\n");
		return ;	
	}

	unsigned char disSize = 3;
	char byUserDiscards[20];
	memset(byUserDiscards, -1, 20);
		
	byUserDiscards[0] = 13;
	byUserDiscards[1] = 16;
	byUserDiscards[2] = 18;
		
	char byDiscards[54] = {0};	
	for ( int i=0; i<disSize; ++i ) 
	{
		byDiscards[ byUserDiscards[i] ] = -1;
	}
	
	bool bStatus = true;
	unsigned char tCard;
	unsigned char m_UserSize = 20;
	for ( int i=0; i<disSize; ++i )
	{
		tCard = byUserDiscards[i];
		if ( tCard > 0 && tCard < 54 ) {
			for ( int j=0; j<m_UserSize; ++j ) 
			{
				if ( byUserDiscards[j] == tCard ) {
					byUserDiscards[j] = -1;
					goto Valid_One;
				}
			}
		}
		bStatus = false; // 打出的牌非法

Valid_One:
	continue;
	
	}
	
	if ( !bStatus ) {
		printf("Error: Invalid Discards\n");
		return;
	}
	
	#if 0
	// 打掉牌后 (排序/不排序)
	for ( int i=0; i<20; ++i )
	{
		for ( int j=i+1; j<20; ++j)
		{
			tCard = byUser1Cards[i];
			byUser1Cards[i] = byUser1Cards[j];
			byUser1Cards[j] = tCard;
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

