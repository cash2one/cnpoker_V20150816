#include "LoginServerSession.h"

#include "PacketHandler.h"

LoginServerSession::LoginServerSession()
{	
}

LoginServerSession::~LoginServerSession()
{
}

void LoginServerSession::Init()
{
	
}

void LoginServerSession::OnRecv(BYTE *pMsg, WORD wSize)
{
	printf("[LoginServerSession::OnRecv]\n");
	printf("call g_PacketHandler.ParsePacket_AL function.\n");
	g_PacketHandler.ParsePacket_AL( this, (MSG_BASE *)pMsg, wSize );
}

void LoginServerSession::OnDisconnect()
{
	ServerSession::OnDisconnect();
}

void LoginServerSession::OnLogString( char * pszLog)
{
	
}
