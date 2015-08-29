#ifndef _GAMEUSERMANAGER_H_INCLUDED_
#define _GAMEUSERMANAGER_H_INCLUDED_

#include <Utility.h>
#include <Common.h>
#include <Network.h>
#include "ServerSession.h"
#include "GameUser.h"

typedef std::map<DWORD, GameUser * > 	MAP_GAMEUSER;
typedef MAP_GAMEUSER::iterator       	MAP_GAMEUSER_ITER;

class GameUserManager : public A::Singleton<GameUserManager>
{
public:
	GameUserManager();
	virtual ~GameUserManager();
	
	BOOL Init();
	
	void Release();
	
	BOOL AddUser( GameUser * pUser );
	GameUser * Find( const DWORD dwKey );
	BOOL Remove( DWORD dwKey );
	
private:
	MAP_GAMEUSER		m_mapGameUser;
};

extern GameUserManager g_GameUserManager;

#endif // _GAMEUSERMANAGER_H_INCLUDED_

