#include "DBFactory.h"

DBFactory::DBFactory()
{
	m_pDBUserPool			 = NULL;
	m_pGameServerSessionPool = NULL;	
	m_pTempServerSessionPool = NULL;	
}

DBFactory::~DBFactory()
{
	if (m_pDBUserPool) 				delete m_pDBUserPool;
	if (m_pGameServerSessionPool) 	delete m_pGameServerSessionPool;
	if (m_pTempServerSessionPool) 	delete m_pTempServerSessionPool;
}

void DBFactory::Init()
{
	m_pDBUserPool 				= new MemoryFactory<DBUser>;
	m_pGameServerSessionPool 	= new MemoryFactory<GameServerSession>; 
	m_pTempServerSessionPool 	= new MemoryFactory<TempServerSession>;
	
	m_pDBUserPool->Initialize(999,1);
	m_pGameServerSessionPool->Initialize(99,1);
	m_pTempServerSessionPool->Initialize(10,1);
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

GameServerSession * DBFactory::AllocGameServerSession() {
	if (m_pGameServerSessionPool == NULL) {
		return NULL;
	}
	return m_pGameServerSessionPool->Alloc();
}

void DBFactory::FreeGameServerSession(GameServerSession * pServerSession) {
	return m_pGameServerSessionPool->Free(pServerSession);
}

TempServerSession * DBFactory::AllocTempServerSession() {
	if (m_pTempServerSessionPool == NULL) {
		return NULL;
	}
	return m_pTempServerSessionPool->Alloc();
}
void DBFactory::FreeTempServerSession(TempServerSession * pServerSession) {
	return m_pTempServerSessionPool->Free(pServerSession);
}

