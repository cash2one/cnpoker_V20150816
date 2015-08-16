#ifndef _AGENT_FACTORY_H_INCLUDED_
#define _AGENT_FACTORY_H_INCLUDED_

#include <Network.h>
#include <Utility.h>
#include "PacketHandler.h"
#include "ServerSession.h"
#include "TempServerSession.h"
#include "GameServerSession.h"
#include "UserSession.h"
#include "TempUserSession.h"
#include "User.h"

using namespace A;

class AgentFactory : public Singleton<AgentFactory>
{
	
public:
	AgentFactory();
	~AgentFactory();

private:	
	MemoryFactory<User> 				* m_pUserPool;
	//MemoryFactory<UserSession> 		* m_pUserSessionPool;
	MemoryFactory<TempUserSession> 		* m_pTempUserSessionPool; 

	MemoryFactory<GameServerSession>	* m_pGameServerSessionPool; 
	MemoryFactory<TempServerSession>	* m_pTempServerSessionPool; 

public:
	void Init(void);
	void Release(void);

	User * AllocUser();
	void FreeUser(User * pUser);
	
	UserSession * AllocUserSession();
	void FreeUserSession(UserSession * pUser);

	TempUserSession * AllocTempUserSession();
	void FreeTempUserSession(TempUserSession * pUser);

	
	GameServerSession * AllocGameServerSession();
	void FreeGameServerSession(GameServerSession * pServerSession);
	
	TempServerSession * AllocTempServerSession();
	void FreeTempServerSession(TempServerSession * pServerSession);
};

#endif
