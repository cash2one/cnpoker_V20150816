#include "AgentFactory.h"

AgentFactory::AgentFactory()
{
	m_pUserPool			 	 = NULL;
	//m_pUserSessionPool		 = NULL;	
	m_pTempUserSessionPool	 = NULL;	
		
	m_pGameServerSessionPool = NULL;	
	m_pTempServerSessionPool = NULL;	
}

AgentFactory::~AgentFactory()
{
	if (m_pUserPool) 				delete m_pUserPool;
	if (m_pTempUserSessionPool) 	delete m_pTempUserSessionPool;	
	
	if (m_pGameServerSessionPool) 	delete m_pGameServerSessionPool;
	if (m_pTempServerSessionPool) 	delete m_pTempServerSessionPool;
}

void AgentFactory::Init()
{
	m_pUserPool 			= new MemoryFactory<User>;
	m_pTempUserSessionPool 	= new MemoryFactory<TempUserSession>;
	
	m_pGameServerSessionPool 	= new MemoryFactory<GameServerSession>; 
	m_pTempServerSessionPool 	= new MemoryFactory<TempServerSession>;
	
	m_pUserPool->Initialize(999,1);
	m_pTempUserSessionPool->Initialize(9,1);
	
	m_pGameServerSessionPool->Initialize(1,1);
	m_pTempServerSessionPool->Initialize(5,1);
}

User * AgentFactory::AllocUser() {
	if (m_pUserPool == NULL) {
		return NULL;
	}
	return m_pUserPool->Alloc();
}
void AgentFactory::FreeUser(User * pUser) {
	return m_pUserPool->Free(pUser);
}

TempUserSession * AgentFactory::AllocTempUserSession() {
	if (m_pTempUserSessionPool == NULL) {
		return NULL;
	}
	return m_pTempUserSessionPool->Alloc();
}
void AgentFactory::FreeTempUserSession(TempUserSession * pUser) {
	return m_pTempUserSessionPool->Free(pUser);
}

GameServerSession * AgentFactory::AllocGameServerSession() {
	if (m_pGameServerSessionPool == NULL) {
		return NULL;
	}
	return m_pGameServerSessionPool->Alloc();
}

void AgentFactory::FreeGameServerSession(GameServerSession * pServerSession) {
	return m_pGameServerSessionPool->Free(pServerSession);
}

TempServerSession * AgentFactory::AllocTempServerSession() {
	if (m_pTempServerSessionPool == NULL) {
		return NULL;
	}
	return m_pTempServerSessionPool->Alloc();
}

void AgentFactory::FreeTempServerSession(TempServerSession * pServerSession) {
	return m_pTempServerSessionPool->Free(pServerSession);
}
