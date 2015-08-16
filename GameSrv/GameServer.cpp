#include "GameServer.h"

#include "InfoParser.h"
//#include "GameFactory.h"

NetworkObject * CreateServerSideAcceptedObject();
VOID DestroyServerSideAcceptedObject( NetworkObject *pNetworkObject );
VOID DestroyServerSideConnectedObject( NetworkObject *pNetworkObject );

GameServer * g_GameServer = NULL;

GameServer::GameServer(void)
{
	m_bShutdown = FALSE;
	m_pIOCPServer = NULL;
}

GameServer::~GameServer(void)
{
	if ( m_pIOCPServer )
		delete m_pIOCPServer;
}

BOOL GameServer::Init()
{
	GameFactory::Instance()->Init(); // Factory <GameUser>
	BOOL bRet = g_InfoParser.Init("./ServerInfo.ini");
	if ( !bRet ) {
		printf("Parse Server Info fail\n");
		return FALSE;
	}
	
	m_pIOCPServer = new IOCPServer;
	
	SYNCHANDLER_DESC desc;
	
	desc.dwSyncHandlerKey				= SERVER_SYNCHANDLER;
	desc.dwMaxAcceptSession				= 0;
	desc.dwMaxConnectSession			= 5;
	desc.dwSendBufferSize				= 2000000;
	desc.dwRecvBufferSize		 		= 2000000;
	desc.dwTimeOut						= 0;
	desc.dwNumberOfAcceptThreads		= 0;
	desc.dwNumberOfIoThreads			= 1;
	desc.dwNumberOfConnectThreads		= 1;
	desc.dwMaxPacketSize				= 60000; // 4096
	desc.fnCreateAcceptedObject			= CreateServerSideAcceptedObject;
	desc.fnDestroyAcceptedObject		= DestroyServerSideAcceptedObject;
	desc.fnDestroyConnectedObject		= DestroyServerSideConnectedObject;
	
	if ( !m_pIOCPServer->Init(&desc, 1) ) {
		return FALSE;
	}
	
	m_pAgentServerSession = GameFactory::Instance()->AllocAgentServerSession();
	if ( m_pAgentServerSession ) {
		SERVER_INFO info = g_InfoParser.GetServerInfo( AGENT_SERVER );
		m_pAgentServerSession->SetAddr( info.m_strIp, info.m_dwPort );
	}
	
	return TRUE;
}

BOOL GameServer::ConnectToServer(ServerSession * pSession)
{
	if (pSession == NULL) {
		return FALSE;
	}
	return m_pIOCPServer->Connect( SERVER_SYNCHANDLER, (NetworkObject *)pSession, "127.0.0.1", 3456 );
	//char szIP[64] = {0};
	//std:: string strIP = pSession->GetConnnectIP();
	//memcpy(szIP, strIP.c_str(), strIP.size()); 
	//return m_pIOCPServer->Connect( SERVER_SYNCHANDLER, (NetworkObject *)pSession, szIP, pSession->GetConnnectPort() );
}


BOOL GameServer::MaintainConnection()
{
	if (m_bShutdown) {
		return FALSE;
	}
	
	if ( m_pAgentServerSession ) {
		if ( m_pAgentServerSession->TryToConnect() ) {
			ConnectToServer(m_pAgentServerSession);
		}
	}
}

#if 0
void GameServer::StartListen()
{
	if ( !m_pIOCPServer->IsListening( SERVER_SYNCHANDLER ) ) {
		if ( !m_pIOCPServer->StartListen( SERVER_SYNCHANDLER, "", 7000 ) ) {
			return;
		}
	}
}
#endif

BOOL GameServer::Update( DWORD dwDeltaTick )
{
	if ( m_pIOCPServer ) {
		m_pIOCPServer->Update();
	}
	
	// Connect other Servers
	MaintainConnection();
	
	return TRUE;
}

BOOL GameServer::SendToAgentServer( BYTE * pMsg, WORD wSize)
{
	printf("[GameServer::SendToAgentServer]\n");
	
	if ( m_pAgentServerSession ) {
		m_pAgentServerSession->Send( pMsg, wSize );
	}
}

//////////////////////////////////////////////////////

NetworkObject * CreateServerSideAcceptedObject() {
	//ServerSession * obj = GameFactory::Instance()->AllocGameUser();
	//return obj;
}

VOID DestroyServerSideAcceptedObject( NetworkObject *pNetworkObject ) {
	//AgentFactory::Instance()->FreeUserSession(pNetworkObject);
}

VOID DestroyServerSideConnectedObject( NetworkObject *pNetworkObject ) {
	
}

