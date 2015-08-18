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
	
	void Broadcast();
	
	static unsigned short GetRandom();
	
	static TableInfo m_TableInfo[1000]; // private to public
private:
	DWORD m_dwUserKey;
	
	unsigned int m_uiRoomNumber; // 房间号
	unsigned int m_uiTableNumber; // 桌子号
	unsigned int m_uiSeat;	// 座位号 0,1,2,3
	
	BYTE m_byCards[CNPOKER_CARD_LEN_2]; // 20
	
	
	
	PlayerInfo m_pPlayer;
	
};

#endif
