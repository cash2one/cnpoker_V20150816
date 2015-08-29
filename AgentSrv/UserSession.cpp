#include "UserSession.h"

UserSession::UserSession()
{	
}

UserSession::~UserSession()
{
}

void UserSession::Init()
{
	m_dwUserID = 0;
	m_pNetGame = NULL;
}

void UserSession::Release()
{
	
}

BOOL UserSession::SendPacket( BYTE *pMsg, WORD wSize )
{
	return Send( (BYTE *)pMsg, wSize );
}

#if 0
void UserSession::SendClient( BYTE *pMsg, WORD wSize )
{

}
	
void UserSession::SendGame( BYTE *pMsg, WORD wSize )
{
	
}
#endif

DWORD UserSession::GetUserID() const
{
	return m_dwUserID;
}

void  UserSession::SetUserID( DWORD dwUserID )
{
	m_dwUserID = dwUserID;
}

/************ protected *************/
void UserSession::OnAccept( DWORD dwNetworkIndex )
{
	
}
	
void UserSession::OnDisconnect()
{
	
}

#if 0
void UserSession::OnRecv(BYTE *pMsg, WORD wSize)
{
	//printf("UserSession OnRecv --> MSG:%s,size:%d\n", (char *)pMsg, wSize);
	//printf("call g_PacketHandler.ParsePacket_CA Function.\n");
	//g_PacketHandler.ParsePacket_CA(this, (MSG_BASE *)pMsg, wSize);
}

void UserSession::OnConnect( BOOL bSuccess, DWORD dwNetworkIndex )
{
	
}
#endif

void UserSession::OnLogString( char * pszLog)
{
	
}
