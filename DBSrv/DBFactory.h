#ifndef _AGENT_FACTORY_H_INCLUDED_
#define _AGENT_FACTORY_H_INCLUDED_

#include <Network.h>
#include <Utility.h>

#include "ServerSession.h"
#include "TempServerSession.h"
#include "GameServerSession.h"
#include "LoginServerSession.h"

#include "DBUser.h"

using namespace A;

class DBFactory : public Singleton<DBFactory>
{
	
public:
	DBFactory();
	~DBFactory();

private:	
	MemoryFactory<DBUser> 				* m_pDBUserPool;
	
	MemoryFactory<TempServerSession>	* m_pTempServerSessionPool;
	MemoryFactory<GameServerSession>	* m_pGameServerSessionPool;
	MemoryFactory<LoginServerSession>	* m_pLoginServerSessionPool; 

public:
	void Init(void);
	void Release(void);

	DBUser * AllocDBUser();
	void FreeDBUser(DBUser * pDBUser);
	
	// Server
	TempServerSession * AllocTempServerSession();
	void FreeTempServerSession(TempServerSession * pServerSession);
	
	GameServerSession * AllocGameServerSession();
	void FreeGameServerSession(GameServerSession * pServerSession);
	
	LoginServerSession * AllocLoginServerSession();
	void FreeLoginServerSession(LoginServerSession * pServerSession);
};

#endif
