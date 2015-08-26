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
	
	DWORD GetHashKey() const { return m_dwUserID; }
	void SetHashKey( DWORD dwID ) { m_dwUserID = dwID; }
	
	unsigned int GetSeat() { return m_uiSeat; }
	unsigned int GetRoomNumber() { return m_uiRoomNumber; }
	unsigned int GetTableNumber() { return m_uiTableNumber; }
	
	void SetRoomNumber(unsigned int unRoomNum) { m_uiRoomNumber = unRoomNum; }
	void SetTableNumber(unsigned int unTableNum) { m_uiTableNumber = unTableNum; }
	void SetSeat(unsigned int unSeat) { m_uiSeat = unSeat; }

	
	PlayerInfo & GetPlayerInfo();

	void SetPlayerInfo(PlayerInfo info);
	
	GameUser * GetNextGameUser();
	
	/****** 游戏响应 ******/
	void StartGame();
	
	void InitCards();
	
	void AllocCards();
	
	void CallLandlord(BYTE byCall); // 叫地主
	void GrabLandlord(); // 抢地主
	void GetExtraCards(); // 获取桌面的三张牌
	
	void ShowCards(); // 明牌
	
	void Discards(BYTE * pCards, unsigned int uiSize); // 出牌
	
	void Pass(); // 要不起
	
	BOOL IsWinTheGame(); // 是否取得胜利
	
	/****** 游戏响应 ******/
	
	void Broadcast(BYTE *pMsg, WORD wSize); // 发送消息给其他游戏玩家
	
	// 找出打出的牌，m_bDiscards， 并检查出牌是否有效
	int FigureOutDiscards(BYTE * pCards, unsigned int uiSize); // 出的牌 3,4,5 --> 3张
	
	
	static TableInfo m_TableInfo[1000]; // private to public	
	
	char m_szCards[CNPOKER_CARD_LEN_2]; // 自己手上的牌 private to public
	
	unsigned int m_uiCardsCount; // 记录玩家手上有多少张牌
	
	static unsigned short GetRandom();
private:
	DWORD m_dwUserID;
	
	unsigned int m_uiRoomNumber; 	// 房间号
	unsigned int m_uiTableNumber; 	// 桌子号
	unsigned int m_uiSeat; 			// 座位号 0,1,2,3
	
	PlayerInfo m_pPlayer;
	
	//static Poker m_sPoker;
};

#endif
