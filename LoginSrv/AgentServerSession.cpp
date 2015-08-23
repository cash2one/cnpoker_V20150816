#include "AgentServerSession.h"

#include "PacketHandler.h"

AgentServerSession::AgentServerSession()
{
	m_userCount = 0;
}

AgentServerSession::~AgentServerSession()
{
}

void AgentServerSession::Init()
{
	ServerSession::Init();
}

void AgentServerSession::Release()
{
	ServerSession::Release();
}

void AgentServerSession::Update()
{
	ServerSession::Update();
}

void AgentServerSession::OnRecv(BYTE *pMsg, WORD wSize)
{
	printf("[AgentServerSession::OnRecv]\n");
	printf("call g_PacketHandler.ParsePacket_AL function.\n");
	g_PacketHandler.ParsePacket_AL( this, (MSG_BASE *)pMsg, wSize);
}

void AgentServerSession::OnConnect( BOOL bSuccess, DWORD dwNetworkIndex )
{
	printf("[LoginServer]: AgentServerSession::OnConnect\n");
	ServerSession::OnConnect( bSuccess, dwNetworkIndex );
	if ( bSuccess ) {
		printf("[AgentServerSession::OnConnect] success.\n");
		printf("Send Server Type.\n");
		ServerSession::SendServerType();
	}
	else
		printf("[LoginServer]: AgentServerSession::OnConnect Fail\n");
}

void AgentServerSession::OnDisconnect()
{
	printf("[AgentServerSession::OnDisconnect]\n");
	ServerSession::OnDisconnect();
}
	
void AgentServerSession::OnLogString( char * pszLog)
{
	
}

// @{ Save its after Login; }
/*
void AgentServerSession::AddUser(LoginUser * pNewUser)
{
	LoginUser * pUser = m_hashUser->GetData( pNewUser->GetHashKey() );
	
	assert( !pUser );
	
	m_hashUser->Add(pNewUser, pNewUser->GetHashKey() );
}

LoginUser * AgentServerSession::FindUser(DWORD dwKey)
{
	return m_hashUser->GetData( dwKey );
}

void AgentServerSession::RemoveUser(DWORD dwKey)
{
	LoginUser * pUser = m_hashUser->GetData( dwKey );
	if ( pUser ) 
	{
		m_hashUser->Remove( dwKey );
	}
}
*/