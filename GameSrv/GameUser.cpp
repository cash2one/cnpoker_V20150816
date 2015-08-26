#include "GameUser.h"


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
	m_dwUserID = 0;
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
	m_pPlayer.m_dwUserID 	= info.m_dwUserID; 	// 用户的Key
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

	BYTE * pMove = GameUser::m_TableInfo[m_uiTableNumber].m_byAllCards;
	pMove[ vecCards[0] ] = CNPOKER_HOLE; // m_byAllCards[4] = 3
	pMove[ vecCards[1] ] = CNPOKER_HOLE; // m_byAllCards[51] = 3
	pMove[ vecCards[2] ] = CNPOKER_HOLE; // m_byAllCards[11] = 3
	
	// 把额外那三张牌给保存下来
	BYTE * pExtraCards = GameUser::m_TableInfo[m_uiTableNumber].m_byExtraCards;
	*pExtraCards++ = vecCards[0]; // 也就是额外那3张牌是 4， 51， 11
	*pExtraCards++ = vecCards[1];
	*pExtraCards = vecCards[2];
		
	// 把牌分成3份
	for(BYTE i=0; i<54; ++i) {
		pMove[ vecCards[i] ] = i%3; // 如: m_byAllCards[15] = 0; m_byAllCards[24] = 1; m_byAllCards[35] = 2; // 第15张是玩家0的牌,24张是玩家1的牌...
	}
}

void GameUser::AllocCards()
{	
	BYTE * pMove = GameUser::m_TableInfo[m_uiTableNumber].m_byAllCards;
	
	GameUser * pUser = this;
	for(int i=0; i<3; ++i)
	{
		if (i != 0) // 
		{
			pUser = GetNextGameUser();
		}
		
		char * pUserCards = pUser->m_szCards;
		for(BYTE i=0; i<CNPOKER_CARD_LEN_1; ++i)
		{
			if ( *pMove == m_uiSeat )
			{
				*pUserCards++ = i;
				pUser->m_uiCardsCount++;
			}
		}
	}
}

void GameUser::CallLandlord(BYTE byCall)
{
	printf("[UserID = %d] : CallLandlord\n", m_dwUserID);	
	GameUser::m_TableInfo[m_uiTableNumber].m_byCallLandlord = byCall;
}

void GameUser::GrabLandlord()
{
	printf("[UserID = %d] : GrabLandlord\n", m_dwUserID);
	
	GameUser::m_TableInfo[m_uiTableNumber].m_uiGrabTimes++; // 抢地主次数加1
}

void GameUser::GetExtraCards()
{
	printf("[GameUser::GetExtraCards] : User %d Get Extra Cards;\n", m_dwUserID);
	BYTE *pMove = GameUser::m_TableInfo[m_uiTableNumber].m_byExtraCards;
	memcpy(m_szCards+17, pMove, 3);
	
	// 调试打印一下额外那三张牌
	for(int i=0; i<3; ++i)
	{
		printf("Extra%d:%d\n", i, *pMove++);
	}
	
	// 重新对牌进行排序
	// ...
}

void GameUser::ShowCards()
{
	printf("[ShowCards] : Table Number = %d\n", m_uiTableNumber);	
	
	MSG_AG_SHOWCARDS_ANC msg2;
	msg2.m_dwUserID = m_dwUserID;
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

	// 判断谁出牌
	if (GameUser::m_TableInfo[m_uiTableNumber].m_uiLastDis == -1) {
		GameUser::m_TableInfo[m_uiTableNumber].m_uiLastDis = m_uiSeat; // 第一次出牌
		GameUser::m_TableInfo[m_uiTableNumber].m_uiLastMsg = m_uiSeat;	
	}
	
	int nRet = PH_0;
	char cThanValue1, cThanCount1, cThanValue2, cThanCount2;
	int eType1 = PH_0, eType2 = PH_0;
	// 判断出牌是否符合逻辑
	eType1 = Poker::Pick(pCards, uiSize, cThanValue1, cThanCount1);		
	if ( eType1 == PH_0 ) {
		MSG_AG_DISCARDS_INVALID msg2;
		msg2.m_dwParameter = m_dwUserID;
		msg2.m_dwErrorCode = eType1; // 错误码
		g_GameServer->SendToAgentServer( (BYTE *)&msg2, sizeof(msg2) );		
		return;
	}	
	
	// 如果 最后一个有牌权的人 不等于 上一次出牌的人， 则需要对出牌先做判断
	if ( GameUser::m_TableInfo[m_uiTableNumber].m_uiLastMsg != GameUser::m_TableInfo[m_uiTableNumber].m_uiLastDis ) {
		// 与之前打的牌比较
		eType2 		= GameUser::m_TableInfo[m_uiTableNumber].m_ePkType;
		cThanValue2 = GameUser::m_TableInfo[m_uiTableNumber].m_byCmpValue;
		cThanCount2 = GameUser::m_TableInfo[m_uiTableNumber].m_byCmpCount;
				
		int nResult = Poker::Than((ePK_TYPE)eType1, cThanValue1, cThanCount1, (ePK_TYPE)eType2, cThanValue2, cThanCount2);
		if ( nResult == PH_0 ) {
			MSG_AG_DISCARDS_INVALID msg2;
			msg2.m_dwParameter = m_dwUserID;
			//msg2.m_dwErrorCode = nResult; // 错误码
			g_GameServer->SendToAgentServer( (BYTE *)&msg2, sizeof(msg2) );		
			return;
		}
	}
	
	// 此时可以直接出牌了
	// 将打出的牌 1.自己手上的牌 设为 -1;  2.桌子上已打出的牌 设为 -1
	int nBack = FigureOutDiscards(pCards, uiSize); // 传入 玩家打出的牌数组 和 个数
	if ( nBack == -1) {
		// 正常来说是要发送一个 出牌无效 的消息返回给 Agent
		printf("[GameUser::Discards] : FigureOutDiscards Invalid.\n");
		MSG_AG_DISCARDS_INVALID msg2;
		msg2.m_dwParameter = m_dwUserID;
		//msg2.m_dwErrorCode = nBack; // 错误码
		g_GameServer->SendToAgentServer( (BYTE *)&msg2, sizeof(msg2) );		
		return;
	}

	MSG_AG_DISCARDS_ANC msg2;
	msg2.m_dwParameter = m_dwUserID;
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
	
	GameUser::m_TableInfo[m_uiTableNumber].m_uiLastDis = m_uiSeat;
	GameUser::m_TableInfo[m_uiTableNumber].m_uiLastMsg = (m_uiSeat + 1) % 3; // 牌权调到下一个人
	
	// 记录打出的最大的牌 及 张数 及 类型
	GameUser::m_TableInfo[m_uiTableNumber].m_ePkType = (ePK_TYPE)nRet;
	GameUser::m_TableInfo[m_uiTableNumber].m_byCmpValue = cThanValue1;
	GameUser::m_TableInfo[m_uiTableNumber].m_byCmpCount = cThanCount1;
}

void GameUser::Pass()
{
	// 只更新牌权 m_uiLastMsg ; 无需更新 上一个出牌的人
	GameUser::m_TableInfo[m_uiTableNumber].m_uiLastMsg = (m_uiSeat + 1) % 3; // 牌权转到下一个人手上
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
		userkey= 	GameUser::m_TableInfo[m_uiTableNumber].m_szUserKey[i];
		if user ！= m_dwUserID
		{
			send()
		}
	}
	#endif
}

int GameUser::FigureOutDiscards(BYTE * pCards, unsigned int uiSize)
{
	if ( m_uiTableNumber > 1000 ) {
		printf("Error: Table Number is not correct.\n");
		return -1;
	}

	bool bStatus = true;
	unsigned char tCard;
	
	char szTmpCards[CNPOKER_CARD_LEN_2] = {0};
	memcpy(szTmpCards, m_szCards, CNPOKER_CARD_LEN_2); // 将牌先复制一份，假如到时出牌不符合，则手上的牌不变
	
	// 判断手上是否有打出的这些牌，有，则对应位置 设为 -1
	for ( int i=0; i<uiSize; ++i )
	{
		tCard = pCards[i]; // 13, 16, 18
		if ( tCard > 0 && tCard < CNPOKER_CARD_LEN_1 ) // 小于54
		{
			for ( int j=0; j<CNPOKER_CARD_LEN_2; ++j ) // 小于20
			{
				if (szTmpCards[j] == tCard)
				{
					szTmpCards[j] = -1;					
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
		return -1;
	}
	
	memcpy(m_szCards, szTmpCards, CNPOKER_CARD_LEN_2);
	
	// 将打出的牌 在 整幅牌 中 置为 -1
	for ( int i=0; i<uiSize; ++i ) 
	{
		GameUser::m_TableInfo[m_uiTableNumber].m_byDiscards[ pCards[i] ] = -1;
	}
	m_uiCardsCount -= uiSize; // 手上留下的牌数
	
	/*
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
	*/	
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

