#ifndef _AGENT_FACTORY_H_INCLUDED_
#define _AGENT_FACTORY_H_INCLUDED_

#include <Network.h>
#include <Utility.h>
#include "PacketHandler.h"
#include "ServerSession.h"
#include "TempServerSession.h"
#include "GameServerSession.h"
#include "DBUser.h"

using namespace A;

class DBFactory : public Singleton<DBFactory>
{
	
public:
	DBFactory();
	~DBFactory();

private:	
	MemoryFactory<DBUser> 				* m_pDBUserPool;
	MemoryFactory<GameServerSession>	* m_pGameServerSessionPool; 
	MemoryFactory<TempServerSession>	* m_pTempServerSessionPool; 

public:
	void Init(void);
	void Release(void);

	DBUser * AllocDBUser();
	void FreeDBUser(DBUser * pDBUser);
		
	GameServerSession * AllocGameServerSession();
	void FreeGameServerSession(GameServerSession * pServerSession);
	
	TempServerSession * AllocTempServerSession();
	void FreeTempServerSession(TempServerSession * pServerSession);
};

#endif
