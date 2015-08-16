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

void GameServerSession::OnDisconnect()
{
	
}

void GameServerSession::OnRecv(BYTE *pMsg, WORD wSize)
{
	printf("[GameServerSession::OnRecv]\n");
	printf("call g_PacketHandler.ParsePacket_GA function.\n");
	g_PacketHandler.ParsePacket_GA( this, (MSG_BASE *)pMsg, wSize );
}

void GameServerSession::OnLogString( char * pszLog)
{
	
}
