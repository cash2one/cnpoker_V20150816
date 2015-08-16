#include "DBServer.h"

NetworkObject * CreateServerSideAcceptedObject();
VOID DestroyServerSideAcceptedObject( NetworkObject *pNetworkObject );
VOID DestroyServerSideConnectedObject( NetworkObject *pNetworkObject );

DBServer * g_DBServer = NULL;

DBServer::DBServer(void)
{
	m_pIOCPServer = NULL;
}

DBServer::~DBServer(void)
{
	if ( m_pIOCPServer )
		delete m_pIOCPServer;
}

BOOL DBServer::Init()
{
	Obj_db_passport.Init();
	
	DBFactory::Instance()->Init();
	
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
	desc[0].dwNumberOfConnectThreads	= 0; // Agent Server don't Active connect.
	desc[0].dwMaxPacketSize				= 60000; //4096
	desc[0].fnCreateAcceptedObject		= CreateServerSideAcceptedObject;
	desc[0].fnDestroyAcceptedObject		= DestroyServerSideAcceptedObject;
	desc[0].fnDestroyConnectedObject	= DestroyServerSideConnectedObject;

	if ( !m_pIOCPServer->Init(desc, 1) ) {
		return FALSE;
	}

	StartServerSideListen();

	return TRUE;	
}

void DBServer::StartServerSideListen() 
{
	if( !m_pIOCPServer->IsListening( SERVER_SYNCHANDLER) ) {
		
		if ( !m_pIOCPServer->StartListen(SERVER_SYNCHANDLER, "127.0.0.1", 3456) ) 
		{
			return;
		}
	}
}

BOOL DBServer::MaintainConnection()
{
	if (m_bShutdown) {
		return TRUE;
	}
}

BOOL DBServer::Update( DWORD dwDeltaTick )
{
	if(m_pIOCPServer)
	{
		m_pIOCPServer->Update();
	}

	// MaintainConnection();
	
	return TRUE;
}

///////////////////////////////////////////////////////////////
NetworkObject * CreateServerSideAcceptedObject() {
	printf("[AgentServer::CreateServerSideAcceptedObject]: Alloc TempServerSession.\n");
	TempServerSession * obj = DBFactory::Instance()->AllocTempServerSession();
	if ( obj == NULL) {
		printf("\nAgentFactory::Instance()->AllocTempServerSession() Fail.\n");
		return NULL;
	}
	return (NetworkObject *)(obj);
}

VOID DestroyServerSideAcceptedObject( NetworkObject *pObjs ) {
	printf("[AgentServer::DestroyServerSideAcceptedObject]: Free GameServerSession.\n");
	GameServerSession * obj = (GameServerSession *)pObjs;
	if ( obj ) {
		printf("AgemtFactory::Instance()->FreeGameServerSession()\n");
		DBFactory::Instance()->FreeGameServerSession(obj);
	}
}

VOID DestroyServerSideConnectedObject( NetworkObject *pNetworkObject ) {
	printf("[AgentServer::DestroyServerSideConnectedObject]: Not Used.\n");
}
