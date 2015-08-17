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
	

	PlayerInfo & GetPlayerInfo();

	void SetPlayerInfo(PlayerInfo info);
	
	void StartGame();
	
	void InitCards();
	void ShowCards();
	void Discards();
	
	static unsigned short GetRandom();
	
	GameUser::Broadcast()
	{
		for ()
		{
			userkey= 	m_TableInfo[m_uiTableNumber ].m_szUserKey[i];
			if user ！= m_dwUserKey
			{
				send()
			}
		}
	}
	
private:
	DWORD m_dwUserKey;
	
	unsigned int m_uiRoomNumber;
	unsigned int m_uiTableNumber;
	
	BYTE m_bySeat;	// 0,1,3
	BYTE byCards[CNPOKER_CARD_LEN_2];
	static TableInfo m_TableInfo[1000];
	
	PlayerInfo m_pPlayer;
	
};

#endif
