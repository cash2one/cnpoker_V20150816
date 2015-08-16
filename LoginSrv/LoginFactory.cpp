#include "LoginFactory.h"

LoginFactory::LoginFactory()
{
	m_pLoginUserPool			= NULL;

	m_pTempServerSessionPool 	= NULL;
	m_pAgentServerSessionPool 	= NULL;
	m_pDBServerSessionPool 		= NULL;
}

LoginFactory::~LoginFactory()
{
	if (m_pLoginUserPool) 			delete m_pLoginUserPool;
	
	if (m_pTempServerSessionPool) 	delete m_pTempServerSessionPool;
	if (m_pAgentServerSessionPool) 	delete m_pAgentServerSessionPool;
	if (m_pDBServerSessionPool) 	delete m_pDBServerSessionPool;
}

void LoginFactory::Init()
{
	m_pLoginUserPool			= new MemoryFactory<LoginUser>;
	
	m_pTempServerSessionPool 	= new MemoryFactory<TempServerSession>;
	m_pAgentServerSessionPool 	= new MemoryFactory<AgentServerSession>;
	m_pDBServerSessionPool 		= new MemoryFactory<DBServerSession>;
	
	m_pLoginUserPool->Initialize(4098,1);
	m_pTempServerSessionPool->Initialize(5,1);
	m_pAgentServerSessionPool->Initialize(1,1);
	m_pDBServerSessionPool->Initialize(1,1);
}

LoginUser * LoginFactory::AllocLoginUser() {
	if (m_pLoginUserPool == NULL) {
		return NULL;
	}
	return m_pLoginUserPool->Alloc();
}
void LoginFactory::FreeLoginUser(LoginUser * pUser) {
	return m_pLoginUserPool->Free(pUser);
}

TempServerSession * LoginFactory::AllocTempServerSession() {
	if (m_pTempServerSessionPool == NULL) {
		return NULL;
	}
	return m_pTempServerSessionPool->Alloc();
}

void LoginFactory::FreeTempServerSession(TempServerSession * pServerSession) {
	return m_pTempServerSessionPool->Free(pServerSession);
}

AgentServerSession * LoginFactory::AllocAgentServerSession() {
	if (m_pAgentServerSessionPool == NULL) {
		return NULL;
	}
	return m_pAgentServerSessionPool->Alloc();
}

void LoginFactory::FreeAgentServerSession(AgentServerSession * pServerSession) {
	return m_pAgentServerSessionPool->Free(pServerSession);
}

DBServerSession * LoginFactory::AllocDBServerSession() {
	if (m_pDBServerSessionPool == NULL) {
		return NULL;
	}
	return m_pDBServerSessionPool->Alloc();
}

void LoginFactory::FreeDBServerSession(DBServerSession * pServerSession) {
	return m_pDBServerSessionPool->Free(pServerSession);
}

