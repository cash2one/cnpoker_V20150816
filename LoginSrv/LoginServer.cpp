#include "LoginServer.h"

NetworkObject * CreateServerSideAcceptedObject();
VOID DestroyServerSideAcceptedObject( NetworkObject *pNetworkObject );
VOID DestroyServerSideConnectedObject( NetworkObject *pNetworkObject );

LoginServer * g_LoginServer = NULL;

LoginServer::LoginServer(void)
{
	m_pIOCPServer = NULL;
	
	m_pDBServerSession = NULL;
}

LoginServer::~LoginServer(void)
{
	if ( m_pIOCPServer )
		delete m_pIOCPServer;
}

BOOL LoginServer::Init()
{
	//LoginFactory::Instance()->Init();
	
	m_pIOCPServer = new IOCPServer;

	SYNCHANDLER_DESC desc[1];
	
	desc[0].dwSyncHandlerKey			= SERVER_SYNCHANDLER;
	desc[0].dwMaxAcceptSession			= 9;
	desc[0].dwMaxConnectSession			= 9;
	desc[0].dwSendBufferSize			= 2000000;
	desc[0].dwRecvBufferSize		 	= 2000000;
	desc[0].dwTimeOut					= 0;
	desc[0].dwNumberOfAcceptThreads		= 1;
	desc[0].dwNumberOfIoThreads			= 1;
	desc[0].dwNumberOfConnectThreads	= 1; // Connect
	desc[0].dwMaxPacketSize				= 60000; //4096
	desc[0].fnCreateAcceptedObject		= CreateServerSideAcceptedObject;
	desc[0].fnDestroyAcceptedObject		= DestroyServerSideAcceptedObject;
	desc[0].fnDestroyConnectedObject	= DestroyServerSideConnectedObject;

	if ( !m_pIOCPServer->Init(desc, 1) ) {
		return FALSE;
	}

	return TRUE;	
}

BOOL LoginServer::Update( DWORD dwDeltaTick )
{
	if(m_pIOCPServer)
	{
		m_pIOCPServer->Update();
	}

	//MaintainConnection();
	
	return TRUE;
}

void LoginServer::Release()
{
	
}

BOOL LoginServer::MaintainConnection()
{
	if (m_bShutdown) {
		return TRUE;
	}
}

BOOL LoginServer::ConnectToServer(ServerSession * pSession)
{
	
}

BOOL LoginServer::SendToDBServer(BYTE * pMsg, WORD wSize)
{
	if (m_pDBServerSession != NULL) {
		m_pDBServerSession->Send(pMsg, wSize);
	}
}


NetworkObject * CreateServerSideAcceptedObject() {
	printf("[LoginServer::CreateServerSideAcceptedObject]: Alloc TempServerSession.\n");
	#if 0
	TempServerSession * obj = AgentFactory::Instance()->AllocTempServerSession();
	if ( obj == NULL) {
		printf("\nAgentFactory::Instance()->AllocTempServerSession() Fail.\n");
		return NULL;
	}
	return (NetworkObject *)(obj);
	#endif
}

VOID DestroyServerSideAcceptedObject( NetworkObject *pObjs ) {
	printf("[LoginServer::DestroyServerSideAcceptedObject]: Free GameServerSession.\n");
	#if 0
	GameServerSession * obj = (GameServerSession *)pObjs;
	if ( obj ) {
		printf("AgemtFactory::Instance()->FreeGameServerSession()\n");
		AgentFactory::Instance()->FreeGameServerSession(obj);
	}
	#endif
}

VOID DestroyServerSideConnectedObject( NetworkObject *pNetworkObject ) {
	printf("[LoginServer::DestroyServerSideConnectedObject]: Not Used.\n");
}

