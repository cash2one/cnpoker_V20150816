#include "PacketHandler.h"
#include "AgentServer.h"
#include "Handler_FromClient.h"
#include "Handler_FromGameServer.h"

PacketHandler g_PacketHandler;

PacketHandler::PacketHandler(void)
{
	m_pFuncMap_CA = new FunctionMap;
	m_pFuncMap_GA = new FunctionMap;
	RegisterHandler();
}

PacketHandler::~PacketHandler(void)
{
	SAFE_DELETE(m_pFuncMap_CA);
	SAFE_DELETE(m_pFuncMap_GA);
}

BOOL PacketHandler::RegisterHandler()
{
	Register_CA();
	Register_GA();
	return TRUE;
}	

void PacketHandler::Register_CA()
{
	AddHandler_CA(CA_Connect, CA_Heartbeat_SYN, Handler_FromClient::OnCA_Heartbeat_SYN);
	
	AddHandler_CA(CA_Client, CA_Login_REQ, Handler_FromClient::OnCA_Login_REQ);
	AddHandler_CA(CA_Client, CA_Login_ANC, Handler_FromClient::OnCA_Login_ANC);
	AddHandler_CA(CA_Client, CA_Relogin_REQ, Handler_FromClient::OnCA_Relogin_REQ);
	AddHandler_CA(CA_Client, CA_Logout_REQ, Handler_FromClient::OnCA_Logout_REQ);

	AddHandler_CA(CA_Game, CA_StartGame_REQ, Handler_FromClient::OnCA_StartGame_REQ);
#if 0	
	AddHandler_CA(CA_Game_Protocol, CA_StartGame_REQ, Handler_FromClient::OnCA_StartGame_REQ);
	AddHandler_CA(CA_Game_Protocol, CA_JoinRoom_REQ, Handler_FromClient::OnCA_JoinRoom_REQ);
	AddHandler_CA(CA_Game_Protocol, CA_JoinTable_REQ, Handler_FromClient::OnCA_JoinTable_REQ);
	AddHandler_CA(CA_Game_Protocol, CA_ShowCards_REQ, Handler_FromClient::OnCA_ShowCards_REQ);
	AddHandler_CA(CA_Game_Protocol, CA_Discards_REQ, Handler_FromClient::OnCA_Discards_REQ);
	AddHandler_CA(CA_Game_Protocol, CA_EndGame_REQ, Handler_FromClient::OnCA_EndGame_REQ);
#endif
}

void PacketHandler::Register_GA()
{
	AddHandler_GA(GA_Connect, GA_StartGame_ANC, Handler_FromGameServer::OnGA_StartGame_ANC);
#if 0
	AddHandler_GA(GA_Connect_Protocol, GA_Heratbeat_ANC, Handler_FromGameServer::OnGA_Heratbeat_ANC);
	
	AddHandler_GA(GA_Client_Protocol, GA_Login_ANC, Handler_FromGameServer::OnGA_Login_ANC);
	AddHandler_GA(GA_Client_Protocol, GA_Relogin_ANC, Handler_FromGameServer::OnGA_Relogin_ANC);
	AddHandler_GA(GA_Client_Protocol, GA_Logout_ANC, Handler_FromGameServer::OnGA_Logout_ANC);
	
	AddHandler_GA(GA_Game_Protocol, GA_StartGame_ANC, Handler_FromGameServer::OnGA_StartGame_ANC);
	AddHandler_GA(GA_Game_Protocol, GA_JoinRoom_ANC, Handler_FromGameServer::OnGA_JoinRoom_ANC);
	AddHandler_GA(GA_Game_Protocol, GA_JoinTable_ANC, Handler_FromGameServer::OnGA_JoinTable_ANC);
	AddHandler_GA(GA_Game_Protocol, GA_ContendWithBanker_ANC, Handler_FromGameServer::OnGA_ContendWithBanker_ANC);
	AddHandler_GA(GA_Game_Protocol, GA_ShowCards_ANC, Handler_FromGameServer::OnGA_ShowCards_ANC);
	AddHandler_GA(GA_Game_Protocol, GA_Discards_ANC, Handler_FromGameServer::OnGA_Discards_ANC);
	AddHandler_GA(GA_Game_Protocol, GA_EndGame_ANC, Handler_FromGameServer::OnGA_EndGame_ANC);
#endif
}

BOOL PacketHandler::AddHandler_CA( WORD category, WORD protocol, fnHandler_c fnHandler)
{
	FUNC_CA * pFuncInfo	= new FUNC_CA;
	printf("category:%d,protocol:%d\n", category, protocol);	
	pFuncInfo->m_dwFunctionKey	= MAKELONG( category, protocol );
	printf("m_dwFunctionKey:%d\n", pFuncInfo->m_dwFunctionKey);
	pFuncInfo->m_fnHandler		= fnHandler;
	
	return m_pFuncMap_CA->Add( pFuncInfo );
}

BOOL PacketHandler::AddHandler_GA( WORD category, WORD protocol, fnHandler fnHandler)
{
	FUNC_GA * pFuncInfo	= new FUNC_GA;
	
	pFuncInfo->m_dwFunctionKey	= MAKELONG( category, protocol );
	pFuncInfo->m_fnHandler		= fnHandler;
	
	return m_pFuncMap_GA->Add( pFuncInfo );
}

VOID PacketHandler::ParsePacket_CA( UserSession * pSession, MSG_BASE * pMsg, WORD wSize )
{
	//ASSERT(NULL != pMsg);
	assert(NULL != pMsg);	

	printf("PacketHandler::ParsePacket CA \n");
	
	FUNC_CA * pFuncInfo = (FUNC_CA *)m_pFuncMap_CA->Find( MAKELONG( pMsg->m_byCategory, pMsg->m_byProtocol ) );
	pFuncInfo->m_fnHandler( pSession, pMsg, wSize );

	//AddLogMsg(LOG_OUT, "ParsePacket_CA Register Message:Category=%d, Protocol=%d\n", pMsg->m_byCategory, pMsg->m_byProtocol);
}

VOID PacketHandler::ParsePacket_GA( ServerSession * pSession, MSG_BASE * pMsg, WORD wSize )
{
	//ASSERT(NULL != pMsg);
	assert(NULL != pMsg);
	printf("PacketHandler::ParsePacket GA \n");
	
	FUNC_GA * pFuncInfo = (FUNC_GA *)m_pFuncMap_GA->Find( MAKELONG( pMsg->m_byCategory, pMsg->m_byProtocol ) );
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
		pSession = AgentServer::Instance()->AddSession(pNetwork);
	}

	if ( pBase->m_byCategory == CA_Client_Protocol ) {
		ParsePacket_CA(pSession, pBase, sizeof(pBase)); // login relogin logout
	}
	else if ( pBase->m_byCategory == CA_Connect_Protocol ) {
		ParsePacket_CA(pSession, pBase, sizeof(pBase)); // Heartbeat
	}
#endif	
	//AddLogMsg(LOG_OUT, "ParsePacket_CA Register Message:Category=%d, Protocol=%d\n", pMsg->m_byCategory, pMsg->m_byProtocol);
}
