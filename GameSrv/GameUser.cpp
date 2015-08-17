#include "GameUser.h"

GameUser::GameUser()
{
	
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

void GameUser::InitCards()
{
	for(int i=0; i<54; ++i)
	{
		m_vecCards.push_back(i);
	}
	random_shuffle( m_vecCards.begin(), m_vecCards.end() );
	for(int i=0; i<54; ++i)
	{
		printf("%d ", m_vecCards[i]);
	}
}
