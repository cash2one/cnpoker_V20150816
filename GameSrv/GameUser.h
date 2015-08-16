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
	
	PlayerInfo & GetPlayerInfo();
	
private:
	unsigned int uiRoomNumber;
	unsigned int uiTableNumber;
	
	static TableInfo m_pTableInfo;
	PlayerInfo m_pPlayer;
};

#endif
