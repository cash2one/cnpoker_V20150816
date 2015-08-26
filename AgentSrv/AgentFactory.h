#ifndef _AGENT_FACTORY_H_INCLUDED_
#define _AGENT_FACTORY_H_INCLUDED_

#include <Network.h>
#include <Utility.h>

#include "ServerSession.h"
#include "TempServerSession.h"
#include "GameServerSession.h"
#include "LoginServerSession.h"

#include "User.h"
#include "UserSession.h"
#include "TempUserSession.h"

#include "RootID.h"

using namespace A;

class AgentFactory : public Singleton<AgentFactory>
{
	
public:
	AgentFactory();
	~AgentFactory();

private:	
	MemoryFactory<User> 				* m_pUserPool;
	MemoryFactory<TempUserSession> 		* m_pTempUserSessionPool; 

	MemoryFactory<TempServerSession>	* m_pTempServerSessionPool; 
	MemoryFactory<GameServerSession>	* m_pGameServerSessionPool; 
	MemoryFactory<LoginServerSession>	* m_pLoginServerSessionPool;

	// Rootid
	MemoryFactory<RootID> 				* m_pRootIDPool;
	
public:
	void Init(void);
	void Release(void);

	// User
	User * AllocUser();
	void FreeUser(User * pUser);

	TempUserSession * AllocTempUserSession();
	void FreeTempUserSession(TempUserSession * pUser);

	// Server
	TempServerSession * AllocTempServerSession();
	void FreeTempServerSession(TempServerSession * pServerSession);
	
	GameServerSession * AllocGameServerSession();
	void FreeGameServerSession(GameServerSession * pServerSession);
	
	LoginServerSession * AllocLoginServerSession();
	void FreeLoginServerSession(LoginServerSession * pServerSession);
	
	// RootID
	RootID * AllocRootID();
	void FreeRootID(RootID * pRoot);
};

#endif
