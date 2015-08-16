#ifndef _LOGIN_FACTORY_H_INCLUDED_
#define _LOGIN_FACTORY_H_INCLUDED_

#include <Network.h>
#include <Utility.h>

#include "TempServerSession.h"
#include "AgentServerSession.h"
#include "DBServerSession.h"

#include "LoginUser.h"

using namespace A;

class LoginFactory : public Singleton<LoginFactory>
{
	
public:
	LoginFactory();
	~LoginFactory();

private:
	// User
	MemoryFactory<LoginUser> 			* m_pLoginUserPool;

	// Server
	MemoryFactory<TempServerSession>	* m_pTempServerSessionPool;	
	MemoryFactory<AgentServerSession>	* m_pAgentServerSessionPool;
	MemoryFactory<DBServerSession>		* m_pDBServerSessionPool;

public:
	void Init(void);
	void Release(void);

	LoginUser * AllocLoginUser();
	void FreeLoginUser(LoginUser * pUser);
	
	// Server
	TempServerSession * AllocTempServerSession();
	void FreeTempServerSession(TempServerSession * pServerSession);
	
	AgentServerSession * AllocAgentServerSession();
	void FreeAgentServerSession(AgentServerSession * pServerSession);
	
	DBServerSession * AllocDBServerSession();
	void FreeDBServerSession(DBServerSession * pServerSession);
};

#endif // _LOGIN_FACTORY_H_INCLUDED_
