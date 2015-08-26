#include "GameServerSession.h"
#include "PacketHandler.h"

GameServerSession::GameServerSession()
	: m_hashDBUser(NULL)
{
	m_hashDBUser = new A::SolarHashTable<DBUser *>;
	m_hashDBUser->Initialize(1024);
}

GameServerSession::~GameServerSession()
{
	m_hashDBUser->RemoveAll();
	delete m_hashDBUser;
	m_hashDBUser = NULL;
}

void GameServerSession::Init()
{	
}

void GameServerSession::OnDisconnect()
{
	
}

void GameServerSession::OnRecv(BYTE *pMsg, WORD wSize)
{
	printf("[GameServerSession::OnRecv]\n");
	printf("call g_PacketHandler.ParsePacket_GA function.\n");
	g_PacketHandler.ParsePacket_GD( this, (MSG_BASE *)pMsg, wSize );
}

void GameServerSession::OnLogString( char * pszLog)
{
	
}


// @{ Save its after Login; }
void GameServerSession::AddUser(DBUser * pNewUser)
{
	DBUser * pUser = m_hashDBUser->GetData( pNewUser->GetHashKey() );
	
	assert( !pUser );
	
	m_hashDBUser->Add(pNewUser, pNewUser->GetHashKey() );
}

DBUser * GameServerSession::FindUser(DWORD dwKey)
{
	return m_hashDBUser->GetData( dwKey );
}

void GameServerSession::RemoveUser(DWORD dwKey)
{
	DBUser * pUser = m_hashDBUser->GetData( dwKey );
	if ( pUser ) 
	{
		m_hashDBUser->Remove( dwKey );
	}
}
