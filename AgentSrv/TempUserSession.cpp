#include "TempUserSession.h"

#include "AgentFactory.h"

#include "UserManager.h"

TempUserSession::TempUserSession()
{	
}

TempUserSession::~TempUserSession()
{
}

void TempUserSession::Init(void)
{
	
}

void TempUserSession::Release(void)
{
	
}
	
void TempUserSession::OnRecv(BYTE *pMsg, WORD wSize)
{
	printf("Enter TempUserSession::OnRecv\n");

	MSG_CA_CONNECTION_ENTERSERVER_SYN * pRecvMsg = (MSG_CA_CONNECTION_ENTERSERVER_SYN *) pMsg;
#if 0	
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
	printf("User Key = %d\n", dwKey);
	obj->SetUserKey(dwKey); // 设置 User Key
	
	Session * pSession = this->m_pSession;
	if ( pSession != NULL ) {
		m_pSession->UnbindNetworkObject();
		pSession->BindNetworkObject(obj);
	}
	printf("TempUserSession change to User Success.\n");

	printf("Send MSG_CA_CONNECTION_ENTERSERVER_ANC.\n");
	printf("Msg size = %d\n", sizeof(MSG_CA_CONNECTION_ENTERSERVER_ANC));
	
	MSG_CA_CONNECTION_ENTERSERVER_ANC ancMsg;
	ancMsg.m_dwParameter = dwKey; // User Key
	pSession->Send( (BYTE *)&ancMsg, sizeof(MSG_CA_CONNECTION_ENTERSERVER_ANC) );
}

void TempUserSession::OnLogString( char * pszLog)
{
	
}
	
BOOL TempUserSession::DeCode ( BYTE * pMsg, WORD wSize )
{
	return TRUE;
}
