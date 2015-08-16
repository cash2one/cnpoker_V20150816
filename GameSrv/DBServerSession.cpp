#include "DBServerSession.h"

DBServerSession::DBServerSession()
{

}

DBServerSession::~DBServerSession()
{
	
}

void DBServerSession::Init()
{
	
}

void DBServerSession::Release()
{
	
}

void DBServerSession::Update()
{
	
}

void DBServerSession::OnRecv(BYTE *pMsg, WORD wSize)
{
	printf(" DBServerSession::OnRecv \n");
	//g_PacketHandler.ParsePacket_CL(pMsg, wSize);
}

void DBServerSession::OnDisconnect()
{
	
}
	
void DBServerSession::OnConnect( BOOL bSuccess, DWORD dwNetworkIndex )
{
	
}

void DBServerSession::OnLogString( char * pszLog)
{
	
}
