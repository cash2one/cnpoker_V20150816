#include "GameServerSession.h"
#include "PacketHandler.h"

GameServerSession::GameServerSession()
{
	m_hashUser = new A::SolarHashTable<DBUser*>;
}

GameServerSession::~GameServerSession()
{
	m_hashUser->RemoveAll();
	delete m_hashUser;
	m_hashUser = NULL;
}

void GameServerSession::Init()
{
	m_hashUser->Initialize(1024);
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
	DBUser * pUser = m_hashUser->GetData( pNewUser->GetHashKey() );
	
	assert( !pUser );
	
	m_hashUser->Add(pNewUser, pNewUser->GetHashKey() );
}

DBUser * GameServerSession::FindUser(DWORD dwKey)
{
	return m_hashUser->GetData( dwKey );
}

void GameServerSession::RemoveUser(DWORD dwKey)
{
	DBUser * pUser = m_hashUser->GetData( dwKey );
	if ( pUser ) 
	{
		m_hashUser->Remove( dwKey );
	}
}
