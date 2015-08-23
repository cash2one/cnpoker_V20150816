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
	AddHandler_LD(LD_ClientLogin, LD_Login_REQ, Handler_FromLoginServer::OnLD_Login_REQ);
	AddHandler_LD(LD_ClientLogin, LD_Logout_REQ, Handler_FromLoginServer::OnLD_Logout_REQ);
}

void PacketHandler::Register_GD()
{
	AddHandler_GD(GD_ClientLogin, GD_Login_REQ, Handler_FromGameServer::OnGD_Login_REQ);
	AddHandler_GD(GD_ClientLogin, GD_Logout_REQ, Handler_FromGameServer::OnGD_Logout_REQ);
	AddHandler_GD(GD_ClientLogin, GD_Save_CMD, Handler_FromGameServer::OnGD_Save_CMD);
	AddHandler_GD(GD_ClientLogin, GD_Update_CMD, Handler_FromGameServer::OnGD_Update_CMD);
}

BOOL PacketHandler::AddHandler_LD( WORD category, WORD protocol, fnHandler fnHandler)
{
	FUNC_LD * pFuncInfo	= new FUNC_LD;
	//printf("category:%d,protocol:%d\n", category, protocol);	
	pFuncInfo->m_dwFunctionKey	= MAKELONG( category, protocol );
	//printf("m_dwFunctionKey:%d\n", pFuncInfo->m_dwFunctionKey);
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
	assert(NULL != pMsg);
	printf("PacketHandler::ParsePacket LD \n");
	
	FUNC_LD * pFuncInfo = (FUNC_LD *)m_pFuncMap_LD->Find( MAKELONG( pMsg->m_byCategory, pMsg->m_byProtocol ) );
	pFuncInfo->m_fnHandler( pSession, pMsg, wSize );

	//AddLogMsg(LOG_OUT, "ParsePacket_GA Register Message:Category=%d, Protocol=%d\n", pMsg->m_byCategory, pMsg->m_byProtocol);
}

VOID PacketHandler::ParsePacket_GD( ServerSession * pSession, MSG_BASE * pMsg, WORD wSize )
{
	assert(NULL != pMsg);

	printf("PacketHandler::ParsePacket GD \n");

	FUNC_GD * pFuncInfo = (FUNC_GD *)m_pFuncMap_GD->Find( MAKELONG( pMsg->m_byCategory, pMsg->m_byProtocol ) );
	pFuncInfo->m_fnHandler( pSession, pMsg, wSize );

	//AddLogMsg(LOG_OUT, "ParsePacket_GA Register Message:Category=%d, Protocol=%d\n", pMsg->m_byCategory, pMsg->m_byProtocol);
}

