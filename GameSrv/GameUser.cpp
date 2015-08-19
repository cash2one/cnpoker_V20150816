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

/**********  出牌算法 **********/
int GameUser::Than(ePK_TYPE _my, char _myValue, char _myCount, ePK_TYPE _other, char _otherValue, char _otherCount)
{
	if ( _my != _other ) {
		if ( _my == PH_MAX )
			return (PH_AGAIN);
		
		if ( _my == PH_4 )
			return (PH_THAN);
		
		return (PH_INVALID);
	}
	
	if ( !(_myValue > PH_C1 && _myValue < PH_End) ) 
		return (PH_INVALID);
	
	if ( _myValue > _otherValue )
		return (PH_THAN);
	
	return (PH_INVALID);
}

int GameUser::Pick(char * PK_Group, char PK_Size, char & thanValue, char & thanCount)
{
	if ( PK_Size <= 0 || PK_Group == NULL ) {
		return (PH_0);
	}
	
	thanCount = 0;
	thanValue = PK_Group[0]; // 取第一个牌为比较值
	
	// (高击中 + 低复杂度) 判断区
	if ( PK_Size == 1 ) {
		return (PH_1); // 单牌
	}
	else if ( PK_Size == 2) {
		if ( PK_Group[0] == PK_Group[1] ) {
			return (PH_2); // 对子
		}
		if ( (PK_Group[0] == 14) && (PK_Group[1] == 15) ) {
			return (PH_MAX); // 王炸
		}
		return -1;
	}
	
	short _Max_Value = 0; 	// PK最大面值
	short _Min_Value = 15; 	// PK最小面值
	short _Max_Count = 0; 	// PK计量最多
	short _Min_Count = 0; 	// PK计量最少
	short _Min_Index = 0; 	// PK计量需要一个下标位来判断	
	
	const short CS_SLOT = 15; // PK的下标最大常量数
	short _PK_Slot[CS_SLOT] = {0}; // PK的SLOT容器
	
	short _idx = 0;
	short _val = 0;
	for ( short i=0; i<(short)PK_Size; ++i)
	{
		_idx = PK_Group[i];
		if ( _idx >= 15 ) {
			return (PH_0);
		}
		
		_PK_Slot[_idx]++;
		_val = _PK_Slot[_idx];
		
		_Max_Value = (_idx >  _Max_Value) ? _idx : _Max_Value; 	// 高位置获取
		_Min_Value = (_idx <= _Min_Value) ? _idx : _Min_Value; 	// 低位置获取
		_Max_Count = (_val >  _Max_Count) ? _val : _Max_Count; 	// 高计量获取
	}
	
	if ( (_Max_Value == _Min_Value) ) { // PK 大小面值都相等时
		if ( PK_Size == 3 ) {
			return (PH_3); // 3个
		}
		if ( PK_Size == 4 ) {
			return (PH_4); // 炸弹
		}
		return (PH_0);
	}
	
	if ( _Max_Count > 4) {
		return (PH_0);
	}
	
	// 得出最小面值的牌
	for (short i=0; i<(short)PK_Size; ++i)
	{
		_idx = PK_Group[i];
		_val = _PK_Slot[_idx];
		_Min_Count = (_val <= _Min_Count) ? _val : _Min_Count; // 低计量获取		
	}
	
	thanValue = _Max_Value; // 到这里取最大值为比较值
	if ( _Max_Count == _Min_Count ) { // PK 数量都相等时
		thanCount = PK_Size / _Max_Count;
		short _Div_0 = PK_Size / (_Max_Value - _Min_Value + 1);
		short _Div_1 = PK_Size % (_Max_Value - _Min_Value + 1);
		short _Div_2 = PK_Size / _Max_Count;
		short _Div_3 = PK_Size % _Max_Count;
		if ( (_Max_Count == _Div_0) && (_Div_1 == 0) ) {
			if ( _Max_Count == 1 ) {
				if ( (_Div_2 >= 5) && (_Div_3 == 0) )
					return (PH_4); // 顺子
				else
					return (PH_0); // 顺不起来
			}
			if ( _Max_Count == 2 ) {
				if ( (_Div_2 >= 3) && (_Div_3 == 0) ) 
					return 0; // 连对
				else
					return (PH_0); // 连不起来
			}
			if ( _Max_Count == 3 ) {
				if ( (_Div_2 >= 2) && (_Div_3 == 0) )
					return 0; // 飞机
				else
					return (PH_0); // 飞不起来
			}
		}
		return (PH_0);		
	}
	
	_idx = 0;
	for (short i=0; i<(short)PK_Size; ++i)
	{
		_idx = PK_Group[i];
		if ( _PK_Slot[_idx] == _Max_Count ) {
			break;
		}
	}
	
	thanValue = _idx; // 到这里取最多牌面值为比较值:
	if ( _Max_Count == 3 ) {
		thanCount = 1;
		if ( (_Min_Count == 1) && (PK_Size == 4) ) {
			return (PH_31); // 三带一
		}
		if ( (_Min_Count == 2) && (PK_Size == 5) ) {
			return (PH_32); // 三带二
		}
		
		// 是否三个连起来了
		short _Three_Max_Value 	= 0; 	// 3同位最大面值
		short _Three_Min_Value 	= 15; 	// 3同位最小面值
		short _Three_Count 		= 0; 	// 3同位个数
		short _Two_Count 		= 0; 	// 2同位个数
		short _One_Count 		= 0; 	// 1同位个数
		for (short i=0; i<(short)CS_SLOT; ++i)
		{
			_idx = _PK_Slot[i];
			if ( _idx == 3 ) {
				_Three_Max_Value = (i >  _Three_Max_Value) ? i : _Three_Max_Value; // 高位置获取
				_Three_Min_Value = (i <= _Three_Min_Value) ? i : _Three_Min_Value; // 低位置获取
				_Three_Count++;
			}
			else if ( _idx == 2 ) {
				_Two_Count++;
			}
			else if ( _idx == 1 ) {
				_One_Count++;
			}
		}
		
		short _Div_0 = (_Three_Max_Value - _Three_Min_Value + 1) / _Three_Count;
		short _Div_1 = (_Three_Max_Value - _Three_Min_Value + 1) % _Three_Count;
		if ( (_Div_0 == 1) && (_Div_1 == 0) ) {
			thanCount = _Three_Count;
			if ( _Three_Count == (_Two_Count * 2 + _One_Count) ) {
				return (PH_31); // 三带一
			}
			return (PH_0);
		}
		return (PH_0);
	}
	
	if ( _Max_Count == 4 ) {
		if ( _Min_Count == 1 ) {
			if ( PK_Size == 5 )
				return (PH_41); // 四带一
			if ( PK_Size == 6 )
				return (PH_411); // 四带二
			return (PH_0);			
		}
		if ( _Min_Count == 2 ) {
			if ( PK_Size == 6 )
				return (PH_42); // 四带一对
			if ( PK_Size == 8 )
				return (PH_422); // 四带两对
			return (PH_0);
		}
		return (PH_0);		
	}
	
	return (PH_0);	
}

int GameUser::OneTimes(char * szPK1, char iSizePK1, char * szPK2, char iSizePK2)
{
	char iThanValue1 = 0;
	char iThanCount1 = 0;
	char iThanValue2 = 0;
	char iThanCount2 = 0;
	
	int e1, e2;
	e1 = Pick(szPK1, iSizePK1, iThanValue1, iThanCount1);
	e2 = Pick(szPK2, iSizePK2, iThanValue2, iThanCount2);
	return Than((ePK_TYPE)e1, iThanValue1, iThanCount1, (ePK_TYPE)e2, iThanValue2, iThanCount2);
}
/**********  end of 出牌算法 **********/

	
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

