#include "User.h"

#include "PacketHandler.h"

User::User()
{	
	//m_pUserSession = NULL;
	//m_pGameSession = NULL;
}

User::~User()
{
}

void User::Login()
{
}

void User::Logout()
{
}

void User::Update()
{
	
}

BOOL User::IsOvertime()
{
	
}

void User::OnAccept( DWORD dwNetworkIndex )
{
	
}

void User::OnDisconnect()
{
	
}

void User::OnRecv(BYTE *pMsg, WORD wSize)
{
	printf("User OnRecv --> MSG:%s,size:%d\n", (char *)pMsg, wSize);
	printf("call g_PacketHandler.ParsePacket_CA Function.\n");
	g_PacketHandler.ParsePacket_CA(this, (MSG_BASE *)pMsg, wSize);	
}

void User::OnConnect( BOOL bSuccess, DWORD dwNetworkIndex )
{
	
}

BOOL User::SendPacket( BYTE *pMsg, WORD wSize )
{
	return UserSession::SendPacket( pMsg, wSize );
}
