#include "TempServerSession.h"
#include "DBServer.h"

TempServerSession::TempServerSession()
{
	m_bFirst = TRUE;
}

TempServerSession::~TempServerSession()
{
	
}

void TempServerSession::Clear()
{
	//m_bFirst = TRUE;
	//ServerSession::Clear();
	ServerSession::Clear();
}

void TempServerSession::OnRecv(BYTE *pMsg, WORD wSize)
{
	assert( m_bFirst == TRUE);
	m_bFirst = FALSE;
	
	printf("Enter TempServerSession::OnRecv.\n");
	
	printf("Ignore varify. Directly Change TempServerSession to GameServerSession.\n");
	
	// 这里应该是要区分是GameServer 还是 DBServer 还是 WorldServer
	// 初步调试统一为GameServer

#if 0
	MSG_SERVER_TYPE * pRecvMsg = (MSG_SERVER_TYPE *)pMsg;
	if ( pRecvMsg->m_byServerType == GAME_SERVER ) {
		ServerSession * Obj = g_DBServer->GetGameServerSession();
		if ( Obj == NULL) {
			printf("\ng_AgentServer->GetGameServerSession Fail.\n");
			return;
		}
		
		Session * pSession = this->m_pSession;
		if ( pSession != NULL ) {
			m_pSession->UnbindNetworkObject();
			pSession->BindNetworkObject(Obj);
		}	
	}
#endif

}

void TempServerSession::OnConnect( BOOL bSuccess, DWORD dwNetworkIndex )
{

}

void TempServerSession::OnLogString( char * pszLog)
{
	
}
