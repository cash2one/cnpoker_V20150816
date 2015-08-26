#include "PacketHandler.h"
#include "AgentServer.h"
#include "Handler_FromClient.h"
#include "Handler_FromGameServer.h"
#include "Handler_FromLoginServer.h"

PacketHandler g_PacketHandler;

PacketHandler::PacketHandler(void)
{
	m_pFuncMap_CA = new FunctionMap;
	m_pFuncMap_AG = new FunctionMap;
	m_pFuncMap_AL = new FunctionMap;
	RegisterHandler();
}

PacketHandler::~PacketHandler(void)
{
	SAFE_DELETE(m_pFuncMap_CA);
	SAFE_DELETE(m_pFuncMap_AG);
	SAFE_DELETE(m_pFuncMap_AL);
}

BOOL PacketHandler::RegisterHandler()
{
	Register_CA();
	Register_AG();
	Register_AL();
	return TRUE;
}	

void PacketHandler::Register_CA()
{
	AddHandler_CA(CA_Connect, CA_Heartbeat_SYN, Handler_FromClient::OnCA_Heartbeat_SYN);
	
	AddHandler_CA(CA_Client, CA_PreLogin_REQ, Handler_FromClient::OnCA_PreLogin_REQ);
	
	AddHandler_CA(CA_Client, CA_Login_REQ, Handler_FromClient::OnCA_Login_REQ);
	
	AddHandler_CA(CA_Client, CA_ReLogin_REQ, Handler_FromClient::OnCA_ReLogin_REQ);
	
	AddHandler_CA(CA_Client, CA_Logout_REQ, Handler_FromClient::OnCA_Logout_REQ);

	// sylar 2015-08-16
	AddHandler_CA(CA_Game, CA_StartGame_REQ, Handler_FromClient::OnCA_StartGame_REQ);	
	AddHandler_CA(CA_Game, CA_JoinRoom_REQ, Handler_FromClient::OnCA_JoinRoom_REQ);
	AddHandler_CA(CA_Game, CA_JoinTable_REQ, Handler_FromClient::OnCA_JoinTable_REQ);
	AddHandler_CA(CA_Game, CA_ShowCards_REQ, Handler_FromClient::OnCA_ShowCards_REQ);
	AddHandler_CA(CA_Game, CA_Discards_BRD, Handler_FromClient::OnCA_Discards_BRD);
	AddHandler_CA(CA_Game, CA_EndGame_SYN, Handler_FromClient::OnCA_EndGame_SYN);
	
	AddHandler_CA(CA_Game, CA_InitCards_BRD, Handler_FromClient::OnCA_InitCards_BRD);
}

void PacketHandler::Register_AG()
{
	AddHandler_AG(AG_Connect, AG_Login_ANC, Handler_FromGameServer::OnAG_Login_ANC);
	AddHandler_AG(AG_Connect, AG_Logout_ANC, Handler_FromGameServer::OnAG_Logout_ANC);
	
	
	AddHandler_AG(AG_Connect, AG_StartGame_ANC, Handler_FromGameServer::OnAG_StartGame_ANC);
	
#if 0
	AddHandler_AG(AG_Connect_Protocol, AG_Heratbeat_ANC, Handler_FromGameServer::OnAG_Heratbeat_ANC);
	
	
	AddHandler_AG(AG_Client_Protocol, AG_Relogin_ANC, Handler_FromGameServer::OnAG_Relogin_ANC);
	
	
	AddHandler_AG(AG_Game_Protocol, AG_StartGame_ANC, Handler_FromGameServer::OnAG_StartGame_ANC);
	AddHandler_AG(AG_Game_Protocol, AG_JoinRoom_ANC, Handler_FromGameServer::OnAG_JoinRoom_ANC);
	AddHandler_AG(AG_Game_Protocol, AG_JoinTable_ANC, Handler_FromGameServer::OnAG_JoinTable_ANC);
	AddHandler_AG(AG_Game_Protocol, AG_ContendWithBanker_ANC, Handler_FromGameServer::OnAG_ContendWithBanker_ANC);
	AddHandler_AG(AG_Game_Protocol, AG_ShowCards_ANC, Handler_FromGameServer::OnAG_ShowCards_ANC);
	AddHandler_AG(AG_Game_Protocol, AG_Discards_ANC, Handler_FromGameServer::OnAG_Discards_ANC);
	AddHandler_AG(AG_Game_Protocol, AG_EndGame_ANC, Handler_FromGameServer::OnAG_EndGame_ANC);
#endif
}

void PacketHandler::Register_AL()
{
	AddHandler_AL(AL_ClientLogin, AL_PreLogin_ANC, Handler_FromLoginServer::OnAL_PreLogin_ANC);
	AddHandler_AL(AL_ClientLogin, AL_Login_ANC, Handler_FromLoginServer::OnAL_Login_ANC);
	
	// add 2015-08-25
	AddHandler_AL(AL_ClientLogin, AL_SaveUserKey_SYN, Handler_FromLoginServer::OnAL_SaveUserKey_SYN);
}

BOOL PacketHandler::AddHandler_CA( WORD category, WORD protocol, fnHandler_c fnHandler)
{
	FUNC_CA * pFuncInfo	= new FUNC_CA;
	//printf("category:%d,protocol:%d\n", category, protocol);	
	pFuncInfo->m_dwFunctionKey	= MAKELONG( category, protocol );
	//printf("m_dwFunctionKey:%d\n", pFuncInfo->m_dwFunctionKey);
	pFuncInfo->m_fnHandler		= fnHandler;
	
	return m_pFuncMap_CA->Add( pFuncInfo );
}

BOOL PacketHandler::AddHandler_AG( WORD category, WORD protocol, fnHandler fnHandler)
{
	FUNC_AG * pFuncInfo	= new FUNC_AG;
	
	pFuncInfo->m_dwFunctionKey	= MAKELONG( category, protocol );
	pFuncInfo->m_fnHandler		= fnHandler;
	
	return m_pFuncMap_AG->Add( pFuncInfo );
}

BOOL PacketHandler::AddHandler_AL( WORD category, WORD protocol, fnHandler fnHandler)
{
	FUNC_AL * pFuncInfo	= new FUNC_AL;
	
	pFuncInfo->m_dwFunctionKey	= MAKELONG( category, protocol );
	pFuncInfo->m_fnHandler		= fnHandler;
	
	return m_pFuncMap_AL->Add( pFuncInfo );
}

VOID PacketHandler::ParsePacket_CA( UserSession * pSession, MSG_BASE * pMsg, WORD wSize )
{
	assert(NULL != pMsg);	
	
	printf("PacketHandler::ParsePacket CA \n");
	
	FUNC_CA * pFuncInfo = (FUNC_CA *)m_pFuncMap_CA->Find( MAKELONG( pMsg->m_byCategory, pMsg->m_byProtocol ) );
	pFuncInfo->m_fnHandler( pSession, pMsg, wSize );

	//AddLogMsg(LOG_OUT, "ParsePacket_CA Register Message:Category=%d, Protocol=%d\n", pMsg->m_byCategory, pMsg->m_byProtocol);
}

VOID PacketHandler::ParsePacket_AG( ServerSession * pSession, MSG_BASE * pMsg, WORD wSize )
{
	assert(NULL != pMsg);
	printf("PacketHandler::ParsePacket AG \n");
	
	FUNC_AG * pFuncInfo = (FUNC_AG *)m_pFuncMap_AG->Find( MAKELONG( pMsg->m_byCategory, pMsg->m_byProtocol ) );
	pFuncInfo->m_fnHandler( pSession, pMsg, wSize );

	//AddLogMsg(LOG_OUT, "ParsePacket_AG Register Message:Category=%d, Protocol=%d\n", pMsg->m_byCategory, pMsg->m_byProtocol);
}

VOID PacketHandler::ParsePacket_AL( ServerSession * pSession, MSG_BASE * pMsg, WORD wSize )
{
	assert(NULL != pMsg);
	printf("PacketHandler::ParsePacket AL \n");
	
	FUNC_AL * pFuncInfo = (FUNC_AL *)m_pFuncMap_AL->Find( MAKELONG( pMsg->m_byCategory, pMsg->m_byProtocol ) );
	pFuncInfo->m_fnHandler( pSession, pMsg, wSize );

	//AddLogMsg(LOG_OUT, "ParsePacket_AG Register Message:Category=%d, Protocol=%d\n", pMsg->m_byCategory, pMsg->m_byProtocol);
}

