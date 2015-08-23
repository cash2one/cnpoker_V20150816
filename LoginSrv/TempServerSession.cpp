#include "TempServerSession.h"
#include "LoginServer.h"
#include "LoginServer.h"

TempServerSession::TempServerSession()
	: m_bFirst(TRUE)
{
}

TempServerSession::~TempServerSession()
{
	
}

void TempServerSession::Clear()
{
	m_bFirst = TRUE;
	ServerSession::Clear();
}


void TempServerSession::OnRecv(BYTE *pMsg, WORD wSize)
{
	assert( m_bFirst == TRUE);
	if ( !m_bFirst)
		return;
	
	m_bFirst = FALSE;
	
	printf("Enter TempServerSession::OnRecv.\n");
	
#if 0	
	MSG_SERVER_TYPE * pRecvMsg = (MSG_SERVER_TYPE *)pMsg;
	if ( pRecvMsg->m_byServerType == AGENT_SERVER ) {
		
		printf("TempServerSession::OnRecv : AGENT_SERVER\n");
		ServerSession * Obj = g_LoginServer->GetAgentServerSession();
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


