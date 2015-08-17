#include "GameServerSession.h"

#include "PacketHandler.h"

GameServerSession::GameServerSession()
{	
}

GameServerSession::~GameServerSession()
{
}

void GameServerSession::Init()
{
	
}

void GameServerSession::OnRecv(BYTE *pMsg, WORD wSize)
{
	printf("[GameServerSession::OnRecv]\n");
	printf("call g_PacketHandler.ParsePacket_AG function.\n");
	g_PacketHandler.ParsePacket_AG( this, (MSG_BASE *)pMsg, wSize );
}

void GameServerSession::OnDisconnect()
{
	ServerSession::OnDisconnect();
}

void GameServerSession::OnLogString( char * pszLog)
{
	
}
