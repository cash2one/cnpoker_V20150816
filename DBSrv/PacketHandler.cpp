#include "PacketHandler.h"
#include "DBServer.h"
#include "Handler_FromGameServer.h"
#include "Handler_FromLoginServer.h"

PacketHandler g_PacketHandler;

PacketHandler::PacketHandler(void)
{
	m_pFuncMap_LD = new FunctionMap;
	m_pFuncMap_GD = new FunctionMap;
	RegisterHandler();
}

PacketHandler::~PacketHandler(void)
{
	SAFE_DELETE(m_pFuncMap_LD);
	SAFE_DELETE(m_pFuncMap_GD);
}

BOOL PacketHandler::RegisterHandler()
{
	Register_LD();
	Register_GD();
	return TRUE;
}

void PacketHandler::Register_LD()
{
	AddHandler_LD(LD_ClientLogin, LD_Login_SYN, Handler_FromLoginServer::OnLD_Login_SYN);
	AddHandler_LD(LD_ClientLogin, LD_Logout_SYN, Handler_FromLoginServer::OnLD_Logout_SYN);
}

void PacketHandler::Register_GD()
{
	AddHandler_GD(GD_ClientLogin, GD_Login_SYN, Handler_FromGameServer::OnGD_Login_SYN);
	AddHandler_GD(GD_ClientLogin, GD_Logout_SYN, Handler_FromGameServer::OnGD_Logout_SYN);
	AddHandler_GD(GD_ClientLogin, GD_Save_CMD, Handler_FromGameServer::OnGD_Save_CMD);
	AddHandler_GD(GD_ClientLogin, GD_Update_CMD, Handler_FromGameServer::OnGD_Update_CMD);
}

BOOL PacketHandler::AddHandler_LD( WORD category, WORD protocol, fnHandler fnHandler)
{
	FUNC_LD * pFuncInfo	= new FUNC_LD;
	printf("category:%d,protocol:%d\n", category, protocol);	
	pFuncInfo->m_dwFunctionKey	= MAKELONG( category, protocol );
	printf("m_dwFunctionKey:%d\n", pFuncInfo->m_dwFunctionKey);
	pFuncInfo->m_fnHandler		= fnHandler;
	
	return m_pFuncMap_LD->Add( pFuncInfo );
}

BOOL PacketHandler::AddHandler_GD( WORD category, WORD protocol, fnHandler fnHandler)
{
	FUNC_GD * pFuncInfo	= new FUNC_GD;
	
	pFuncInfo->m_dwFunctionKey	= MAKELONG( category, protocol );
	pFuncInfo->m_fnHandler		= fnHandler;
	
	return m_pFuncMap_GD->Add( pFuncInfo );
}

VOID PacketHandler::ParsePacket_LD( ServerSession * pSession, MSG_BASE * pMsg, WORD wSize )
{
	//ASSERT(NULL != pMsg);
	assert(NULL != pMsg);
	printf("PacketHandler::ParsePacket GA \n");
	
	FUNC_LD * pFuncInfo = (FUNC_LD *)m_pFuncMap_LD->Find( MAKELONG( pMsg->m_byCategory, pMsg->m_byProtocol ) );
	pFuncInfo->m_fnHandler( pSession, pMsg, wSize );

	//AddLogMsg(LOG_OUT, "ParsePacket_GA Register Message:Category=%d, Protocol=%d\n", pMsg->m_byCategory, pMsg->m_byProtocol);
}

VOID PacketHandler::ParsePacket_GD( ServerSession * pSession, MSG_BASE * pMsg, WORD wSize )
{
	assert(NULL != pMsg);

	printf("PacketHandler::ParsePacket GA \n");

	FUNC_GD * pFuncInfo = (FUNC_GD *)m_pFuncMap_GD->Find( MAKELONG( pMsg->m_byCategory, pMsg->m_byProtocol ) );
	pFuncInfo->m_fnHandler( pSession, pMsg, wSize );

	//AddLogMsg(LOG_OUT, "ParsePacket_GA Register Message:Category=%d, Protocol=%d\n", pMsg->m_byCategory, pMsg->m_byProtocol);
}

VOID PacketHandler::ParsePacket(NetworkObject * pNetwork, char * pMsg)
{
	//ASSERT(NULL != pMsg);
	assert(NULL != pMsg);
	printf("PacketHandler::ParsePacket Function \n");

	MSG_BASE * pBase = (MSG_BASE *)pMsg;
	printf("Category:%d,Protocol:%d\n", pBase->m_byCategory, pBase->m_byProtocol);

#if 0
	ServerSession * pSession = AgentServer::Instance()->FindSession(pNetwork);
	if ( pSession == NULL ) {
		pSession = DBServer::Instance()->AddSession(pNetwork);
	}

	if ( pBase->m_byCategory == CA_Client_Protocol ) {
		ParsePacket_AD(pSession, pBase, sizeof(pBase)); // login relogin logout
	}
	else if ( pBase->m_byCategory == CA_Connect_Protocol ) {
		ParsePacket_GD(pSession, pBase, sizeof(pBase)); // Heartbeat
	}
#endif	
	
}
