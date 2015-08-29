#include "AgentFactory.h"

AgentFactory::AgentFactory()
{
	m_pUserPool			 	 = NULL;
	m_pTempUserSessionPool	 = NULL;	
	
	m_pTempServerSessionPool = NULL;
	m_pGameServerSessionPool = NULL;		
	m_pLoginServerSessionPool = NULL;
	
	// Rootid
	m_pRootIDPool = NULL;
}

AgentFactory::~AgentFactory()
{
	if (m_pUserPool) 				delete m_pUserPool;
	if (m_pTempUserSessionPool) 	delete m_pTempUserSessionPool;	
	
	if (m_pTempServerSessionPool) 	delete m_pTempServerSessionPool;
	if (m_pGameServerSessionPool) 	delete m_pGameServerSessionPool;
	if (m_pLoginServerSessionPool) 	delete m_pLoginServerSessionPool;
	
	// Rootid
	if (m_pRootIDPool) 				delete m_pRootIDPool;
}

void AgentFactory::Init()
{
	m_pUserPool 			= new MemoryFactory<User>;
	m_pTempUserSessionPool 	= new MemoryFactory<TempUserSession>;
	
	m_pTempServerSessionPool 	= new MemoryFactory<TempServerSession>;
	m_pGameServerSessionPool 	= new MemoryFactory<GameServerSession>; 
	m_pLoginServerSessionPool 	= new MemoryFactory<LoginServerSession>; 
	
	m_pRootIDPool 				= new MemoryFactory<RootID>; 
	
	// User
	m_pUserPool->Initialize(999,1);
	m_pTempUserSessionPool->Initialize(99,1); // 多少才合适?
	// Server
	m_pTempServerSessionPool->Initialize(5,1); // 多少才合适?
	m_pGameServerSessionPool->Initialize(1,1);
	m_pLoginServerSessionPool->Initialize(9,1); // 多少才合适?
	
	// RootID
	m_pRootIDPool->Initialize(999,1); // 多少才合适?
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
	//TempUserSession * pSession = m_pTempUserSessionPool->Alloc();
	//if ( pSession != NULL ) {
	//	pSession->Release();
	//}
		
	//return pSession;
}
void AgentFactory::FreeTempUserSession(TempUserSession * pUser) {
	return m_pTempUserSessionPool->Free(pUser);
}

TempServerSession * AgentFactory::AllocTempServerSession() {
	if (m_pTempServerSessionPool == NULL) {
		return NULL;
	}
	TempServerSession * pSession = m_pTempServerSessionPool->Alloc();
	if ( pSession != NULL ) {
		pSession->Clear();
	}
		
	return pSession;
}

void AgentFactory::FreeTempServerSession(TempServerSession * pServerSession) {
	return m_pTempServerSessionPool->Free(pServerSession);
}

GameServerSession * AgentFactory::AllocGameServerSession() {
	if (m_pGameServerSessionPool == NULL) {
		return NULL;
	}
	GameServerSession * pSession = m_pGameServerSessionPool->Alloc();
	if ( pSession != NULL ) {
		pSession->Clear();
	}
		
	return pSession;	
}

void AgentFactory::FreeGameServerSession(GameServerSession * pServerSession) {
	return m_pGameServerSessionPool->Free(pServerSession);
}

LoginServerSession * AgentFactory::AllocLoginServerSession() {
	if (m_pLoginServerSessionPool == NULL) {
		return NULL;
	}
	LoginServerSession * pSession = m_pLoginServerSessionPool->Alloc();
	if ( pSession != NULL ) {
		pSession->Clear();
	}
		
	return pSession;
}

void AgentFactory::FreeLoginServerSession(LoginServerSession * pServerSession) {
	return m_pLoginServerSessionPool->Free(pServerSession);
}

// Rootid
RootID * AgentFactory::AllocRootID()
{
	if (m_pRootIDPool == NULL) {
		return NULL;
	}
	RootID * pRoot = NULL;
	pRoot = m_pRootIDPool->Alloc();
	if ( pRoot != NULL ) {
		pRoot->Clear();
	}
		
	return pRoot;	
}

void AgentFactory::FreeRootID(RootID * pRoot)
{
	return m_pRootIDPool->Free(pRoot);
}

