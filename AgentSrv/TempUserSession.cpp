#include "TempUserSession.h"

#include "AgentFactory.h"

#include "UserManager.h"
#include "RootidManager.h"

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

#if 0
BOOL TempUserSession::IsSameRootID( BYTE * pUserKey1, BYTE * pUserKey2 )
{
	if ( ( pUserKey1 == NULL ) || ( pUserKey2 == NULL ) ) {
		return FALSE;
	}
	
	int nLen1 = strlen(pUserKey1);
	int nLen2 = strlen(pUserKey2);
	if ( nLen1 != nLen2 ) {
		return FALSE;
	}
	printf("nLen1 = %d\n", nLen1);
	for( int i=0; i<CODE_KEY_LEN; ++i )
	{
		if ( pUserKey1[i] != pUserKey2[i] ) {
			return FALSE;
		}
	}

	return TRUE;
}	
#endif

void TempUserSession::OnRecv(BYTE *pMsg, WORD wSize)
{
	printf(">>>> [TempUserSession::OnRecv]\n");
	
	assert( m_bFirst == TRUE );
	if ( !m_bFirst ) {
		printf("Debug m_bFirst != TRUE. So return.\n");
		return;
	}
	
	MSG_CA_LOGIN_REQ * pRecvMsg = (MSG_CA_LOGIN_REQ *) pMsg;
	printf("RootID = %d, UserKey = %s\n", pRecvMsg->m_uiRootID, pRecvMsg->m_byUserKey);
	
	RootID * pRoot = RootidManager::Instance()->FindRootID( pRecvMsg->m_uiRootID );
	if ( pRoot == NULL ) {
		printf("\n[RootidManager::Instance()->FindRootID] Fail.\n");
		// 发送出错信息
		MSG_CA_LOGIN_NAK msgError;
		msgError.m_dwParameter = pRecvMsg->m_dwParameter; // User ID
		msgError.m_dwErrorCode = 1234;

		Session * pSession = this->m_pSession;
		if ( pSession != NULL ) {
			//m_pSession->UnbindNetworkObject();
			pSession->BindNetworkObject(this);
		}
		pSession->Send( (BYTE *)&msgError, sizeof(MSG_CA_LOGIN_NAK) );
		
		printf("\n>>>> Free TempUserSesion <<<<\n");
		AgentFactory::Instance()->FreeTempUserSession(this);		
		return;
	}
		
	BOOL bRet = pRoot->IsSameUserKey(pRecvMsg->m_byUserKey);
	if ( !bRet ) {
		printf("\n[RootidManager::Instance()->IsSameRootID] Fail.\n");
		// 发送出错信息
		//MSG_CA_LOGIN_NAK msgError;
		return;
	}
	
	User * obj = AgentFactory::Instance()->AllocUser(); // 
	if ( obj == NULL) {
		printf("\nAgentFactory::Instance()->AllocUser() Fail.\n");
		return;
	}
	
	DWORD dwID = g_UserManager.AddUser(obj);
	printf("g_UserManager Alloc User ID = %d\n", dwID);
	obj->SetUserID(dwID); // 设置 User ID
	
	Session * pSession = this->m_pSession;
	if ( pSession != NULL ) {
		m_pSession->UnbindNetworkObject();
		pSession->BindNetworkObject(obj);
	}
	printf("TempUserSession ==> User Success.\n");
	
	printf("Send MSG_CA_CONNECTION_ENTERSERVER_ANC.\n");
	printf("Msg size = %d\n", sizeof(MSG_CA_CONNECTION_ENTERSERVER_ANC));
	
	MSG_CA_CONNECTION_ENTERSERVER_ANC ancMsg;
	ancMsg.m_dwParameter = dwID; // User Key
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
