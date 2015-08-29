#include "PacketHandler.h"
#include "GameServer.h"
#include "Handler_FromAgentServer.h"
#include "Handler_FromDBServer.h"
#include "Handler_FromGameServer.h"

PacketHandler g_PacketHandler;

PacketHandler::PacketHandler(void)
{
	m_pFuncMap_AG = new FunctionMap;
	m_pFuncMap_DG = new FunctionMap;
	RegisterHandler();
}

PacketHandler::~PacketHandler(void)
{
	SAFE_DELETE(m_pFuncMap_AG);
	SAFE_DELETE(m_pFuncMap_DG);
}

BOOL PacketHandler::RegisterHandler()
{
	Register_AG();
	Register_DG();
	return TRUE;
}	

void PacketHandler::Register_AG()
{
	AddHandler_AG( AG_Connect, AG_Login_REQ, Handler_FromAgentServer::OnAG_Login_REQ );
	AddHandler_AG( AG_Connect, AG_Logout_REQ, Handler_FromAgentServer::OnAG_Logout_REQ );	
	
	AddHandler_AG( AG_Connect, AG_StartGame_REQ, Handler_FromAgentServer::OnAG_StartGame_REQ );	
	AddHandler_AG( AG_Connect, AG_JoinRoom_REQ, Handler_FromAgentServer::OnAG_JoinRoom_REQ );
	AddHandler_AG( AG_Connect, AG_JoinTable_REQ, Handler_FromAgentServer::OnAG_JoinTable_REQ );
	AddHandler_AG( AG_Connect, AG_ShowCards_REQ, Handler_FromAgentServer::OnAG_ShowCards_REQ );
	AddHandler_AG( AG_Connect, AG_Discards_REQ, Handler_FromAgentServer::OnAG_Discards_REQ );
	AddHandler_AG( AG_Connect, AG_EndGame_SYN, Handler_FromAgentServer::OnAG_EndGame_SYN );
	
	AddHandler_AG( AG_Connect, AG_InitCards_BRD, Handler_FromAgentServer::OnAG_InitCards_BRD );
}

void PacketHandler::Register_DG()
{
	AddHandler_DG(GD_ClientLogin, GD_Login_ANC, Handler_FromDBServer::OnGD_Login_ANC);
	
	AddHandler_DG(GD_ClientLogin, GD_Login_NAK, Handler_FromDBServer::OnGD_Login_NAK);
	
	AddHandler_DG(GD_ClientLogin, GD_Logout_ANC, Handler_FromDBServer::OnGD_Logout_ANC);
	
}

BOOL PacketHandler::AddHandler_AG( WORD category, WORD protocol, fnHandler fnHandler)
{
	FUNC_AG * pFuncInfo	= new FUNC_AG;
	//printf("category:%d,protocol:%d\n", category, protocol);	
	pFuncInfo->m_dwFunctionKey	= MAKELONG( category, protocol );
	//printf("m_dwFunctionKey:%d\n", pFuncInfo->m_dwFunctionKey);
	pFuncInfo->m_fnHandler		= fnHandler;
	
	return m_pFuncMap_AG->Add( pFuncInfo );
}

BOOL PacketHandler::AddHandler_DG( WORD category, WORD protocol, fnHandler fnHandler)
{
	FUNC_DG * pFuncInfo	= new FUNC_DG;
	
	pFuncInfo->m_dwFunctionKey	= MAKELONG( category, protocol );
	pFuncInfo->m_fnHandler		= fnHandler;
	
	return m_pFuncMap_DG->Add( pFuncInfo );
}

VOID PacketHandler::ParsePacket_AG( ServerSession * pSession, MSG_BASE * pMsg, WORD wSize )
{
	assert(NULL != pMsg);
	
	FUNC_AG * pFuncInfo = (FUNC_AG *)m_pFuncMap_AG->Find( MAKELONG( pMsg->m_byCategory, pMsg->m_byProtocol ) );
	pFuncInfo->m_fnHandler( pSession, pMsg, wSize );

	//AddLogMsg(LOG_OUT, "ParsePacket_CA Register Message:Category=%d, Protocol=%d\n", pMsg->m_byCategory, pMsg->m_byProtocol);
}

VOID PacketHandler::ParsePacket_DG( ServerSession * pSession, MSG_BASE * pMsg, WORD wSize )
{
	assert(NULL != pMsg);
	
	FUNC_DG * pFuncInfo = (FUNC_DG *)m_pFuncMap_DG->Find( MAKELONG( pMsg->m_byCategory, pMsg->m_byProtocol ) );
	pFuncInfo->m_fnHandler( pSession, pMsg, wSize );

	//AddLogMsg(LOG_OUT, "ParsePacket_DG Register Message:Category=%d, Protocol=%d\n", pMsg->m_byCategory, pMsg->m_byProtocol);
}

