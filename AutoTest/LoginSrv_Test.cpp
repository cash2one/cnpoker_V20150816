
AgentServer::AgentServer(void)
{
	m_pIOCPServer = NULL;
	
	m_pGameServer = NULL;
}

AgentServer::~AgentServer(void)
{
	if ( m_pIOCPServer )
		delete m_pIOCPServer;
}


BOOL DBTestServer::Init()
{
	AgentFactory::Instance()->Init();
	
	m_pIOCPServer = new IOCPServer;

	SYNCHANDLER_DESC desc[2];
	
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

	if ( !m_pIOCPServer->Init(desc, 2) ) {
		return FALSE;
	}


	m_pGameServer = AgentFactory::Instance()->AllocGameServerSession();
	if ( m_pGameServer == NULL) {
		printf("[AgentFactory::Instance()->AllocGameServerSession] fail\n");
		return FALSE;
	}
	
	return TRUE;
	
}

