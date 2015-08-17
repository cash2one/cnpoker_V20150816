#include "AgentServer.h"

#include "UserManager.h"
#include "InfoParser.h"


NetworkObject * CreateServerSideAcceptedObject();
VOID DestroyServerSideAcceptedObject( NetworkObject *pNetworkObject );
VOID DestroyServerSideConnectedObject( NetworkObject *pNetworkObject );

NetworkObject * CreateClientSideAcceptedObject();
VOID DestroyClientSideAcceptedObject( NetworkObject * pNetworkObject );
VOID DestroyClientSideConnectedObject( NetworkObject * pNetworkObject );

AgentServer * g_AgentServer = NULL;

AgentServer::AgentServer(void)
{
	m_bShutdown		= FALSE;
	
	m_pIOCPServer 	= NULL;
	
	m_pGameServer 	= NULL;
}

AgentServer::~AgentServer(void)
{
	if ( m_pIOCPServer )
		delete m_pIOCPServer;
}

BOOL AgentServer::Init()
{
	AgentFactory::Instance()->Init();
	BOOL bRet = g_InfoParser.Init("./ServerInfo.ini");
	if ( !bRet ) {
		printf("Parse Server Info fail\n");
		return FALSE;
	}
		
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
	desc[0].dwNumberOfConnectThreads	= 1; // Agent Connect -> GameServer
	desc[0].dwMaxPacketSize				= 60000; //4096
	desc[0].fnCreateAcceptedObject		= CreateServerSideAcceptedObject;
	desc[0].fnDestroyAcceptedObject		= DestroyServerSideAcceptedObject;
	desc[0].fnDestroyConnectedObject	= DestroyServerSideConnectedObject;

	desc[1].dwSyncHandlerKey 			= CLIENT_SYNCHANDLER;
	desc[1].dwMaxAcceptSession			= 700;
	desc[1].dwMaxConnectSession			= 0;
	desc[1].dwSendBufferSize			= 1024 * 60; //60000
	desc[1].dwRecvBufferSize			= 1024 * 60; //60000
	desc[1].dwTimeOut					= 0;
	desc[1].dwNumberOfAcceptThreads		= 1;
	desc[1].dwNumberOfIoThreads			= 1;
	desc[1].dwNumberOfConnectThreads	= 0;
	desc[1].dwMaxPacketSize				= 1024 * 10;	//4096
	desc[1].fnCreateAcceptedObject		= CreateClientSideAcceptedObject;
	desc[1].fnDestroyAcceptedObject		= DestroyClientSideAcceptedObject;
	desc[1].fnDestroyConnectedObject	= DestroyClientSideConnectedObject;

	if ( !m_pIOCPServer->Init(desc, 2) ) {
		return FALSE;
	}

	g_UserManager.InitUserSize( MAX_PLAYER_NUM ); // 1000
	
	StartServerSideListen();
	StartClientSideListen();

	m_pGameServer = AgentFactory::Instance()->AllocGameServerSession();
	if ( m_pGameServer == NULL) {
		printf("[AgentFactory::Instance()->AllocGameServerSession] fail\n");
		return FALSE;
	}
	
	#if 0
	m_pGameServer = AgentFactory::Instance()->AllocGameServerSession();
	if ( m_pGameServer ) {
		SERVER_INFO info = g_InfoParser.GetServerInfo( GAME_SERVER ); // 获取 GAME Server 的 IP 与 Port
		m_pGameServer->SetAddr( info.m_strIp, info.m_dwPort ); // 7100		
		//m_pIOCPServer->Connect( SERVER_SYNCHANDLER, (NetworkObject *)m_pGameServer, "127.0.0.1", 7100 ); // GAME Port 7100
	}	
	#endif
	
	return TRUE;	
}

void AgentServer::StartServerSideListen() 
{
	if( !m_pIOCPServer->IsListening( SERVER_SYNCHANDLER) ) {
		
		if ( !m_pIOCPServer->StartListen(SERVER_SYNCHANDLER, "127.0.0.1", 7000) ) // AGENT Port 7000
		{
			return;
		}
	}
}

void AgentServer::StartClientSideListen()
{
	if ( !m_pIOCPServer->IsListening( CLIENT_SYNCHANDLER) ) {
		
		if ( !m_pIOCPServer->StartListen(CLIENT_SYNCHANDLER, "127.0.0.1", 1234) ) // Clinet Port 1234
		{
			return;
		}
	}
}

BOOL AgentServer::MaintainConnection()
{
	if (m_bShutdown) {
		return TRUE;
	}
	
	// 主动连接 Game Server
	if ( m_pGameServer ) {
		m_pGameServer->TryToConnect();
	}
}

BOOL AgentServer::Update( DWORD dwDeltaTick )
{
	if(m_pIOCPServer)
	{
		m_pIOCPServer->Update();
	}

	//MaintainConnection();
	
	return TRUE;
}

BOOL AgentServer::ConnectToServer(ServerSession * pSession, char * pszIP, WORD wPort)
{
	//printf("AgentServer::ConnectToServer Function\n");
	if (pSession == NULL) {
		return FALSE;
	}
	//printf("IP = %s, Port = %d\n", pszIP, wPort);
	
	return m_pIOCPServer->Connect( SERVER_SYNCHANDLER, (NetworkObject *)pSession, pszIP, wPort );
	//return m_pIOCPServer->Connect( SERVER_SYNCHANDLER, (NetworkObject *)pSession, "127.0.0.1", 3456 );	
}

BOOL AgentServer::SendToGameServer( BYTE * pMsg, WORD wSize)
{
	printf("[AgentServer::SendToGameServer]\n");
	
	if ( m_pGameServer ) {
		return m_pGameServer->Send( pMsg, wSize );
	}
	return FALSE;
}

ServerSession * AgentServer::GetGameServerSession() const
{
	return m_pGameServer;
}

///////////////////////////////////////////////////////////////

NetworkObject * CreateServerSideAcceptedObject() {
	printf("[AgentServer::CreateServerSideAcceptedObject]: Alloc TempServerSession.\n");
	TempServerSession * obj = AgentFactory::Instance()->AllocTempServerSession();
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
		AgentFactory::Instance()->FreeGameServerSession(obj);
	}
}

VOID DestroyServerSideConnectedObject( NetworkObject *pNetworkObject ) {
	printf("[AgentServer::DestroyServerSideConnectedObject]: Not Used.\n");
}

NetworkObject * CreateClientSideAcceptedObject() {
	printf("[AgentServer::CreateClientSideAcceptedObject]: Alloc TempUserSession.\n");
	TempUserSession * obj = AgentFactory::Instance()->AllocTempUserSession();
	if ( obj == NULL) {
		printf("\nAgentFactory::Instance()->AllocTempUserSession() Fail.\n");
		return NULL;
	}
	return (NetworkObject *)(obj);
}

VOID DestroyClientSideAcceptedObject( NetworkObject * pObjs ) {
	printf("[AgentServer::DestroyClientSideAcceptedObject]: Free User.\n");
	User * obj = (User *)pObjs;
	if ( obj ) {
		printf("User Key:%d\n, Num counts =%d\n", obj->GetUserKey(), g_UserManager.GetUserNums());
		g_UserManager.Remove(obj->GetUserKey());
		printf("AgemtFactory::Instance()->FreeUser()\n");
		AgentFactory::Instance()->FreeUser(obj);		
	}
}

VOID DestroyClientSideConnectedObject( NetworkObject * pNetworkObject ) {
	printf("[AgentServer::DestroyClientSideConnectedObject]: Not Used.\n");
}
