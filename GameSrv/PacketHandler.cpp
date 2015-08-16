#include "PacketHandler.h"
#include "GameServer.h"
#include "Handler_FromAgentServer.h"
#include "Handler_FromDBServer.h"

PacketHandler g_PacketHandler;

PacketHandler::PacketHandler(void)
{
	m_pFuncMap_GA = new FunctionMap;
	m_pFuncMap_DG = new FunctionMap;
	RegisterHandler();
}

PacketHandler::~PacketHandler(void)
{
	SAFE_DELETE(m_pFuncMap_GA);
	SAFE_DELETE(m_pFuncMap_DG);
}

BOOL PacketHandler::RegisterHandler()
{
	Register_GA();
	Register_DG();
	return TRUE;
}	

void PacketHandler::Register_GA()
{
	AddHandler_GA( GA_Connect, GA_StartGame_REQ, Handler_FromAgentServer::OnGA_StartGame_REQ );
}

void PacketHandler::Register_DG()
{
#if 0	
	AddHandler_CA(CA_Game_Protocol, CA_StartGame_REQ, Handler_FromClient::OnCA_StartGame_REQ);
#endif
}

BOOL PacketHandler::AddHandler_GA( WORD category, WORD protocol, fnHandler fnHandler)
{
	FUNC_GA * pFuncInfo	= new FUNC_GA;
	printf("category:%d,protocol:%d\n", category, protocol);	
	pFuncInfo->m_dwFunctionKey	= MAKELONG( category, protocol );
	printf("m_dwFunctionKey:%d\n", pFuncInfo->m_dwFunctionKey);
	pFuncInfo->m_fnHandler		= fnHandler;
	
	return m_pFuncMap_GA->Add( pFuncInfo );
}

BOOL PacketHandler::AddHandler_DG( WORD category, WORD protocol, fnHandler fnHandler)
{
	FUNC_DG * pFuncInfo	= new FUNC_DG;
	
	pFuncInfo->m_dwFunctionKey	= MAKELONG( category, protocol );
	pFuncInfo->m_fnHandler		= fnHandler;
	
	return m_pFuncMap_DG->Add( pFuncInfo );
}

VOID PacketHandler::ParsePacket_GA( ServerSession * pSession, MSG_BASE * pMsg, WORD wSize )
{
	// ASSERT(NULL != pMsg);
	
	FUNC_GA * pFuncInfo = (FUNC_GA *)m_pFuncMap_GA->Find( MAKELONG( pMsg->m_byCategory, pMsg->m_byProtocol ) );
	pFuncInfo->m_fnHandler( pSession, pMsg, wSize );

	//AddLogMsg(LOG_OUT, "ParsePacket_CA Register Message:Category=%d, Protocol=%d\n", pMsg->m_byCategory, pMsg->m_byProtocol);
}

VOID PacketHandler::ParsePacket_DG( ServerSession * pSession, MSG_BASE * pMsg, WORD wSize )
{
	// ASSERT(NULL != pMsg);
	
	FUNC_DG * pFuncInfo = (FUNC_DG *)m_pFuncMap_DG->Find( MAKELONG( pMsg->m_byCategory, pMsg->m_byProtocol ) );
	pFuncInfo->m_fnHandler( pSession, pMsg, wSize );

	//AddLogMsg(LOG_OUT, "ParsePacket_GA Register Message:Category=%d, Protocol=%d\n", pMsg->m_byCategory, pMsg->m_byProtocol);
}

