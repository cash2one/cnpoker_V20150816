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
	
	unsigned int GetSeat() { return m_uiSeat; }
	unsigned int GetRoomNumber() { return m_uiRoomNumber; }
	unsigned int GetTableNumber() { return m_uiTableNumber; }
	
	void SetRoomNumber(unsigned int unRoomNum) { m_uiRoomNumber = unRoomNum; }
	void SetTableNumber(unsigned int unTableNum) { m_uiTableNumber = unTableNum; }
	void SetSeat(unsigned int unSeat) { m_uiSeat = unSeat; }

	/**********  出牌算法 **********/
	int Than(ePK_TYPE _my, char _myValue, char _myCount, ePK_TYPE _other, char _otherValue, char _otherCount);
	int Pick(char * PK_Group, char PK_Size, char & thanValue, char & thanCount);
	int OneTimes(char * szPK1, char iSizePK1, char * szPK2, char iSizePK2);
	
	/*******************************/
	
	PlayerInfo & GetPlayerInfo();

	void SetPlayerInfo(PlayerInfo info);
	
	GameUser * GetNextGameUser();
	
	void StartGame();
	
	void InitCards();
	
	void AllocCards();
	
	void ShowCards();
	
	void Discards(BYTE * pCards, unsigned int uiSize);
	
	BOOL IsWinTheGame();
	
	void Broadcast(BYTE *pMsg, WORD wSize); // 发送消息给其他游戏玩家
	
	// 找出打出的牌，m_bDiscards， 并检查出牌是否有效
	void FigureOutDiscards(BYTE * pCards, unsigned int uiSize); // 出的牌 3,4,5 --> 3张

	
	
	static TableInfo m_TableInfo[1000]; // private to public	
	
	char m_szCards[CNPOKER_CARD_LEN_2]; // 自己手上的牌 private  to public
	
	unsigned int m_uiCardsCount; // 记录一共有多少张牌
	
	static unsigned short GetRandom();
private:
	DWORD m_dwUserKey;
	
	unsigned int m_uiRoomNumber; 	// 房间号
	unsigned int m_uiTableNumber; 	// 桌子号
	unsigned int m_uiSeat; 			// 座位号 0,1,2,3
	
	PlayerInfo m_pPlayer;
};

#endif
