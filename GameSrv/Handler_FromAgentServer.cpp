#include "Handler_FromAgentServer.h"

#include "GameServer.h"

Handler_FromAgentServer::Handler_FromAgentServer() 
{
	
}

Handler_FromAgentServer::~Handler_FromAgentServer() 
{
	
}

HANDLER_IMPL( AG_StartGame_REQ )
{
	printf("Handle GA_StartGame_REQ\n");
	
#if 0	
	MSG_GA_START_GAME_REQ * pRecv = (MSG_GA_START_GAME_REQ *)pMsg;
	printf("Category=%d,Protocol=%d, UserKey=%d\n", pRecv->m_byCategory, pRecv->m_byProtocol, pRecv->m_dwUserKey); // m_byCategory: 40, m_byProtocol: 2000
	
	MSG_GA_START_GAME_ANC msg2;
	msg2.m_dwUserKey = pRecv->m_dwUserKey;
	//msg2.m_byCategory = GA_Connect; // 40
	//msg2.m_byProtocol = GA_StartGame_ANC; // 2001
	
	g_GameServer->SendToAgentServer( (BYTE *)&msg2, sizeof(msg2) );
#endif
}

HANDLER_IMPL( AG_JoinRoom_REQ )
{
	
}

HANDLER_IMPL( AG_JoinTable_REQ )
{
	
}

HANDLER_IMPL( AG_ShowCards_REQ )
{
	
}

HANDLER_IMPL( AG_Discards_REQ )
{
	
}

HANDLER_IMPL( AG_EndGame_REQ )
{
	
}

HANDLER_IMPL( AG_InitCards_BRD )
{
	
}
