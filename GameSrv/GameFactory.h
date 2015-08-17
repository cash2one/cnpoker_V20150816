#ifndef _GAMEFACTORY_H_INCLUDED_
#define _GAMEFACTORY_H_INCLUDED_

#include <Network.h>
#include <Utility.h>
#include <Common.h>
#include "PacketHandler.h"
#include "ServerSession.h"
#include "AgentServerSession.h"
#include "DBServerSession.h"
#include "GameUser.h"

using namespace A;

class GameFactory : public Singleton<GameFactory>
{
public:
	GameFactory();
	~GameFactory();

private:
	MemoryFactory<GameUser> 			* m_pGameUserPool;
	MemoryFactory<AgentServerSession> 	* m_pAgentServerPool;
	MemoryFactory<DBServerSession> 		* m_pDBServerPool;
	
public:
	void Init(void);
	void Release(void);

	GameUser * AllocGameUser();
	void FreeGameUser(GameUser * pObjs);
	
	AgentServerSession * AllocAgentServerSession();
	void FreeAgentServerSession(AgentServerSession * pObjs);
	
	DBServerSession * AllocDBServerSession();
	void FreeDBServerSession(DBServerSession * pObjs);
};

#endif
