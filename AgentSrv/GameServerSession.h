#ifndef _GAMESERVERSESSION_H_INCLUDED_
#define _GAMESERVERSESSION_H_INCLUDED_

#include <Utility.h>
#include <Common.h>
#include <Network.h>
//#include "AgentServer.h" 
#include "ServerSession.h"

class GameServerSession : public ServerSession
{
public:
	GameServerSession();
	virtual ~GameServerSession();
	
	eSERVER_TYPE    GetServerType() { return GAME_SERVER; }
	
	virtual void    Init();
	
public:

	virtual void	OnDisconnect();
	virtual void	OnRecv(BYTE *pMsg, WORD wSize);
	virtual void	OnLogString( char * pszLog);
};

#endif // _GAMESERVERSESSION_H_INCLUDED_
