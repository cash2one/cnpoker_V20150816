#ifndef _GAMEUSER_H_INCLUDED_
#define _GAMEUSER_H_INCLUDED_

#include <Network.h>
#include <Utility.h>
#include <Common.h>
#include <Public.h>

using namespace A;

class GameUser
{
public:
	GameUser();
	~GameUser();
	
	void LoginRoom(unsigned int _roomid);
	void logoutRoom();
	
	void LoginTable(unsigned int _tableid);
	void logoutTable();
	
	DWORD GetHashKey() const { return m_dwUserKey; }
	void SetHashKey( DWORD dwKey ) { m_dwUserKey = dwKey; }
	
	void SetRoomNumber(unsigned int unRoomNum) { m_uiRoomNumber = unRoomNum; }
	void SetTableNumber(unsigned int unTableNum) { m_uiTableNumber = unTableNum; }
	void SetSeat(unsigned int unSeat) { m_uiSeat = unSeat; }

	
	
	PlayerInfo & GetPlayerInfo();

	void SetPlayerInfo(PlayerInfo info);
	
	GameUser * GetNextGameUser();
	
	void StartGame();
	
	void InitCards();
	
	void AllocCards();
	
	void ShowCards();
	void Discards();
	
	void Broadcast(BYTE *pMsg, WORD wSize); // 发送消息给其他游戏玩家
	
	unsigned int GetSeat() { return m_uiSeat; }
	unsigned int GetRoomNumber() { return m_uiRoomNumber; }
	unsigned int GetTableNumber() { return m_uiTableNumber; }
	
	//  找出打出的牌，m_bDiscards数组对应位置 置1
	void FigureOutDiscards(BYTE * pCards, unsigned int uiSize) // 出的牌 3,4,5 --> 3张
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
	//void GetCards(BYTE * byCards) { memcpy(byCards, m_byCards, CNPOKER_CARD_LEN_2); }
	
	static unsigned short GetRandom();
	
	static TableInfo m_TableInfo[1000]; // private to public	
	
	BYTE m_byCards[CNPOKER_CARD_LEN_2]; // 自己手上的牌 private  to public
	
	unsigned int m_uiCardsCount; // 记录一共有多少张牌
private:
	DWORD m_dwUserKey;
	
	unsigned int m_uiRoomNumber; // 房间号
	unsigned int m_uiTableNumber; // 桌子号
	unsigned int m_uiSeat;	// 座位号 0,1,2,3
	
	PlayerInfo m_pPlayer;
};

#endif
