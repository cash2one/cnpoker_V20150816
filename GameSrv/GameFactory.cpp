#include "GameFactory.h"

GameFactory::GameFactory()
{
	m_pGameUserPool	= NULL;
	
	m_pDBServerPool = NULL;
	m_pAgentServerPool = NULL;
}

GameFactory::~GameFactory()
{
	if (m_pGameUserPool) {
		delete m_pGameUserPool;
		m_pGameUserPool = NULL;
	}
	
	if (m_pDBServerPool) {
		delete m_pDBServerPool;
		m_pDBServerPool = NULL;		
	}
	
	if (m_pAgentServerPool) {
		delete m_pAgentServerPool;
		m_pAgentServerPool = NULL;		
	}
}

void GameFactory::Init()
{
	m_pGameUserPool = new MemoryFactory<GameUser>;
	m_pGameUserPool->Initialize(999,1);
	
	m_pDBServerPool = new MemoryFactory<DBServerSession>;
	m_pDBServerPool->Initialize(1,1);
	
	m_pAgentServerPool = new MemoryFactory<AgentServerSession>;
	m_pAgentServerPool->Initialize(2,1);
}

GameUser * GameFactory::AllocGameUser() {
	if (m_pGameUserPool == NULL) {
		return NULL;
	}
	return m_pGameUserPool->Alloc();
}

void GameFactory::FreeGameUser(GameUser * pObjs) {
	return m_pGameUserPool->Free(pObjs);
}

DBServerSession * GameFactory::AllocDBServerSession()
{
	if (m_pDBServerPool == NULL) {
		return NULL;
	}
	return m_pDBServerPool->Alloc();
}

void GameFactory::FreeDBServerSession(DBServerSession * pObjs)
{
	return m_pDBServerPool->Free(pObjs);
}

AgentServerSession * GameFactory::AllocAgentServerSession() {
	if (m_pAgentServerPool == NULL) {
		return NULL;
	}
	return m_pAgentServerPool->Alloc();
}

void GameFactory::FreeAgentServerSession(AgentServerSession * pObjs) {
	return m_pAgentServerPool->Free(pObjs);
}
