#include "TempUserSession.h"

#include "AgentFactory.h"

#include "UserManager.h"

TempUserSession::TempUserSession()
	: m_bFirst(TRUE)
{	
}

TempUserSession::~TempUserSession()
{
}

void TempUserSession::Init()
{
	UserSession::Init();
}

void TempUserSession::Release()
{
	UserSession::Release();
	m_bFirst = TRUE;
}
	
void TempUserSession::OnRecv(BYTE *pMsg, WORD wSize)
{
	printf(">>>> [TempUserSession::OnRecv]\n");
	
	assert( m_bFirst == TRUE );
	if ( !m_bFirst ) {
		printf("Debug m_bFirst != TRUE. So return.\n");
		return;
	}
		
	
#if 0		
	MSG_CA_CONNECTION_ENTERSERVER_SYN * pRecvMsg = (MSG_CA_CONNECTION_ENTERSERVER_SYN *) pMsg;

	if ( !DeCode (pRecvMsg->m_byTicket, TICKET_LEN) ) {
		MSG_CA_CONNECTION_ENTERSERVER_NAK msgError;
		Send( (BYTE *)pMsg, sizeof(MSG_CA_CONNECTION_ENTERSERVER_NAK) );
		return;
	}
#endif

	User * obj = AgentFactory::Instance()->AllocUser(); // TempUser UserSession  // 
	if ( obj == NULL) {
		printf("\nAgentFactory::Instance()->AllocUser() Fail.\n");
		return;
	}
	
	DWORD dwKey = g_UserManager.AddUser(obj);
	printf("g_UserManager Alloc User Key = %d\n", dwKey);
	obj->SetUserKey(dwKey); // 设置 User Key
	
	Session * pSession = this->m_pSession;
	if ( pSession != NULL ) {
		m_pSession->UnbindNetworkObject();
		pSession->BindNetworkObject(obj);
	}
	printf("TempUserSession ==> User Success.\n");
	
	printf("Send MSG_CA_CONNECTION_ENTERSERVER_ANC.\n");
	printf("Msg size = %d\n", sizeof(MSG_CA_CONNECTION_ENTERSERVER_ANC));
	
	MSG_CA_CONNECTION_ENTERSERVER_ANC ancMsg;
	ancMsg.m_dwParameter = dwKey; // User Key
	pSession->Send( (BYTE *)&ancMsg, sizeof(MSG_CA_CONNECTION_ENTERSERVER_ANC) );
	
	printf("\n>>>> Free TempUserSesion <<<<\n");	
	AgentFactory::Instance()->FreeTempUserSession(this);
}

void TempUserSession::OnLogString( char * pszLog)
{
	
}
	
BOOL TempUserSession::DeCode ( BYTE * pMsg, WORD wSize )
{
	return TRUE;
}
