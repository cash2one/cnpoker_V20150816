#include "DBFactory.h"

DBFactory::DBFactory()
{
	m_pDBUserPool			 = NULL;
	
	m_pTempServerSessionPool = NULL;
	m_pGameServerSessionPool = NULL;	
	m_pLoginServerSessionPool = NULL;
}

DBFactory::~DBFactory()
{
	if (m_pDBUserPool) 				delete m_pDBUserPool;
	
	if (m_pTempServerSessionPool) 	delete m_pTempServerSessionPool;
	if (m_pGameServerSessionPool) 	delete m_pGameServerSessionPool;
	if (m_pLoginServerSessionPool) 	delete m_pLoginServerSessionPool;
}

void DBFactory::Init()
{
	m_pDBUserPool 				= new MemoryFactory<DBUser>;
	
	m_pTempServerSessionPool 	= new MemoryFactory<TempServerSession>;
	m_pGameServerSessionPool 	= new MemoryFactory<GameServerSession>;
	m_pLoginServerSessionPool 	= new MemoryFactory<LoginServerSession>; 
	
	
	m_pDBUserPool->Initialize(999,1);
	
	m_pTempServerSessionPool->Initialize(10,1);
	m_pGameServerSessionPool->Initialize(9,1);
	m_pLoginServerSessionPool->Initialize(9,1); // ???
}

DBUser * DBFactory::AllocDBUser() {
	if (m_pDBUserPool == NULL) {
		return NULL;
	}
	return m_pDBUserPool->Alloc();
}

void DBFactory::FreeDBUser(DBUser * pDBUser) {
	return m_pDBUserPool->Free(pDBUser);
}

TempServerSession * DBFactory::AllocTempServerSession() {
	if (m_pTempServerSessionPool == NULL) {
		return NULL;
	}
	TempServerSession * pSession = m_pTempServerSessionPool->Alloc();
	if ( pSession != NULL ) {
		pSession->Clear();
	}
	
	return pSession;
}

void DBFactory::FreeTempServerSession(TempServerSession * pServerSession) {
	return m_pTempServerSessionPool->Free(pServerSession);
}

GameServerSession * DBFactory::AllocGameServerSession() {
	if (m_pGameServerSessionPool == NULL) {
		return NULL;
	}
	return m_pGameServerSessionPool->Alloc();
}

void DBFactory::FreeGameServerSession(GameServerSession * pServerSession) {
	return m_pGameServerSessionPool->Free(pServerSession);
}


LoginServerSession * DBFactory::AllocLoginServerSession() {
	if (m_pLoginServerSessionPool == NULL) {
		return NULL;
	}
	return m_pLoginServerSessionPool->Alloc();	
}

void DBFactory::FreeLoginServerSession(LoginServerSession * pServerSession) {
	return m_pLoginServerSessionPool->Free(pServerSession);
}

