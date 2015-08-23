#include "PacketHandler.h"
#include "Handler_FromAgentServer.h"
#include "Handler_FromDBServer.h"

PacketHandler g_PacketHandler;

PacketHandler::PacketHandler(void)
{
	m_pFuncMap_AL = new FunctionMap;
	m_pFuncMap_LD = new FunctionMap;
	RegisterHandler();
}

PacketHandler::~PacketHandler(void)
{
	SAFE_DELETE(m_pFuncMap_AL);
	SAFE_DELETE(m_pFuncMap_LD);
}

BOOL PacketHandler::RegisterHandler()
{
	Register_AL();
	Register_LD();
	return TRUE;
}

void PacketHandler::Register_AL()
{
	AddHandler_AL(AL_ClientLogin, AL_PreLogin_REQ, Handler_FromAgentServer::OnAL_PreLogin_REQ);
	
	AddHandler_AL(AL_ClientLogin, AL_Login_REQ, Handler_FromAgentServer::OnAL_Login_REQ);
	AddHandler_AL(AL_ClientLogin, AL_ReLogin_REQ, Handler_FromAgentServer::OnAL_ReLogin_REQ);
	
	AddHandler_AL(AL_ClientLogin, AL_Logout_REQ, Handler_FromAgentServer::OnAL_Logout_REQ);
}

void PacketHandler::Register_LD()
{
	AddHandler_LD(LD_ClientLogin, LD_Login_ANC, Handler_FromDBServer::OnLD_Login_ANC);
	AddHandler_LD(LD_ClientLogin, LD_Logout_ANC, Handler_FromDBServer::OnLD_Logout_ANC);
}

BOOL PacketHandler::AddHandler_AL( WORD category, WORD protocol, fnHandler fnHandler)
{
	FUNC_AL * pFuncInfo	= new FUNC_AL;
	//printf("category:%d,protocol:%d\n", category, protocol);	
	pFuncInfo->m_dwFunctionKey	= MAKELONG( category, protocol );
	//printf("m_dwFunctionKey:%d\n", pFuncInfo->m_dwFunctionKey);
	pFuncInfo->m_fnHandler		= fnHandler;
	
	return m_pFuncMap_AL->Add( pFuncInfo );
}

BOOL PacketHandler::AddHandler_LD( WORD category, WORD protocol, fnHandler fnHandler)
{
	FUNC_LD * pFuncInfo	= new FUNC_LD;
	
	pFuncInfo->m_dwFunctionKey	= MAKELONG( category, protocol );
	pFuncInfo->m_fnHandler		= fnHandler;
	
	return m_pFuncMap_LD->Add( pFuncInfo );
}

VOID PacketHandler::ParsePacket_AL( ServerSession * pSession, MSG_BASE * pMsg, WORD wSize )
{
	assert(NULL != pMsg);
	printf("PacketHandler::ParsePacket AL \n");
	
	FUNC_AL * pFuncInfo = (FUNC_AL *)m_pFuncMap_AL->Find( MAKELONG( pMsg->m_byCategory, pMsg->m_byProtocol ) );
	pFuncInfo->m_fnHandler( pSession, pMsg, wSize );

	//AddLogMsg(LOG_OUT, "ParsePacket_GA Register Message:Category=%d, Protocol=%d\n", pMsg->m_byCategory, pMsg->m_byProtocol);
}

VOID PacketHandler::ParsePacket_LD( ServerSession * pSession, MSG_BASE * pMsg, WORD wSize )
{
	assert(NULL != pMsg);

	printf("PacketHandler::ParsePacket LD \n");

	FUNC_LD * pFuncInfo = (FUNC_LD *)m_pFuncMap_LD->Find( MAKELONG( pMsg->m_byCategory, pMsg->m_byProtocol ) );
	pFuncInfo->m_fnHandler( pSession, pMsg, wSize );

	//AddLogMsg(LOG_OUT, "ParsePacket_GA Register Message:Category=%d, Protocol=%d\n", pMsg->m_byCategory, pMsg->m_byProtocol);
}
