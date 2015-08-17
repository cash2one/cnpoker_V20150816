#ifndef _GAMEUSER_H_INCLUDED_
#define _GAMEUSER_H_INCLUDED_

#include <Network.h>
#include <Utility.h>
#include <Common.h>

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
	
	
	// 设置玩家信息
	void SetPlayerInfo(PlayerInfo info);
	// 获取用户信息
	PlayerInfo & GetPlayerInfo();
	
	void InitCards();
	
private:
	DWORD m_dwUserKey;
	
	unsigned int m_uiRoomNumber;
	unsigned int m_uiTableNumber;
	
	static TableInfo m_pTableInfo[1000];
	PlayerInfo m_pPlayer;
	
	vector<int> m_vecCards;
};

#endif
