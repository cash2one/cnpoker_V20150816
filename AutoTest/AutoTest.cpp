#include "AutoTest.h"


AutoTest * g_AutoTest = NULL;

AutoTest::AutoTest(void)
{
	m_pIOCPServer = NULL;
	
	m_pDBServer = NULL;
	m_pGameServer = NULL;
}

AutoTest::~AutoTest(void)
{
	if ( m_pIOCPServer ) {
		delete m_pIOCPServer;
		m_pIOCPServer = NULL;
	}

	if ( m_pDBServer ) {
		delete m_pDBServer;
		m_pDBServer = NULL;
	}
	
	if ( m_pGameServer ) {
		delete m_pGameServer;
		m_pGameServer = NULL;
	}
}

BOOL AutoTest::Init()
{	
	m_pIOCPServer = new IOCPServer;

	SYNCHANDLER_DESC desc[1];
	
	desc[0].dwSyncHandlerKey			= SERVER_SYNCHANDLER;
	desc[0].dwMaxAcceptSession			= 0;
	desc[0].dwMaxConnectSession			= 5;
	desc[0].dwSendBufferSize			= 200000;
	desc[0].dwRecvBufferSize		 	= 200000;
	desc[0].dwTimeOut					= 0;
	desc[0].dwNumberOfAcceptThreads		= 0;
	desc[0].dwNumberOfIoThreads			= 0;
	desc[0].dwNumberOfConnectThreads	= 1; // 连接线程
	desc[0].dwMaxPacketSize				= 4096;
	desc[0].fnCreateAcceptedObject		= NULL;
	desc[0].fnDestroyAcceptedObject		= NULL;
	desc[0].fnDestroyConnectedObject	= NULL;

	if ( !m_pIOCPServer->Init(desc, 1) ) {
		return FALSE;
	}

	m_pDBServer = new ServerSession;
	
	//m_pGameServer = new DBServerSession;
	//assert(m_pGameServer != NULL);
	//m_pGameServer->SetAddr( "127.0.0.1", 6666 );

	return TRUE;	
}

BOOL AutoTest::ConnectToServer(ServerSession * pSession)
{
	if (pSession == NULL) {
		return FALSE;
	}
	return m_pIOCPServer->Connect( SERVER_SYNCHANDLER, (NetworkObject *)pSession, "127.0.0.1", 6666 );
}

BOOL AutoTest::MaintainConnection()
{
	if (m_bShutdown) {
		return TRUE;
	}
	
	if ( m_pDBServer ) {
		if ( m_pDBServer->TryToConnect() ) {
			ConnectToServer(m_pDBServer);
		}
	}
}

BOOL AutoTest::Update( DWORD dwDeltaTick )
{
	if(m_pIOCPServer)
	{
		m_pIOCPServer->Update();
	}
	
	return TRUE;
}

#if 0
BOOL AutoTest::SendToGameServer( BYTE * pMsg, WORD wSize)
{
	printf("[AutoTest::SendToGameServer]\n");
	
	if ( m_pGameServer ) {
		m_pGameServer->Send(pMsg, wSize);
	}
}

ServerSession * AutoTest::GetGameServerSession() const
{
	return m_pGameServer;
}
#endif


	