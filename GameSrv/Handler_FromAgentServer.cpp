#include "Handler_FromAgentServer.h"

#include "GameServer.h"
#include "GameUserManager.h"

Handler_FromAgentServer::Handler_FromAgentServer() 
{
	
}

Handler_FromAgentServer::~Handler_FromAgentServer() 
{
	
}

HANDLER_IMPL( AG_StartGame_REQ )
{
	printf("AG_StartGame_REQ\n");
	
	MSG_AG_START_GAME_REQ * pRecvMsg = (MSG_AG_START_GAME_REQ *)pMsg;
	DWORD dwUserKey = pRecvMsg->m_dwUserKey;
	
	GameUser * pUser = GameFactory::Instance()->AllocGameUser();
	if ( pUser != NULL ) {
		pUser->SetHashKey(dwUserKey);
	}
	
	
#if 0	
	MSG_AG_START_GAME_REQ * pRecvMsg = (MSG_GA_START_GAME_REQ *)pMsg;
	printf("Category=%d,Protocol=%d, UserKey=%d\n", pRecvMsg->m_byCategory, pRecvMsg->m_byProtocol, pRecvMsg->m_dwUserKey); // m_byCategory: 40, m_byProtocol: 2000
	
	MSG_AG_START_GAME_ANC msg2;
	msg2.m_dwUserKey = pRecvMsg->m_dwUserKey;

	g_GameServer->SendToAgentServer( (BYTE *)&msg2, sizeof(msg2) );
#endif
}

HANDLER_IMPL( AG_JoinRoom_REQ )
{
	printf("AG_JoinRoom_REQ\n");
	
	MSG_AG_JOINROOM_REQ * pRecvMsg = (MSG_AG_JOINROOM_REQ *)pMsg;
	DWORD dwUserKey = pRecvMsg->m_dwUserKey;
	BYTE byRoomNumber = pRecvMsg->m_byRoomNumber;
	
	GameUser * pUser = g_GameUserManager.Find(dwUserKey);
	if ( pUser == NULL ) {
		printf("Can't find User %d\n", dwUserKey);
		return;
	}
	pUser->SetRoomNumber(byRoomNumber);
	
}

HANDLER_IMPL( AG_JoinTable_REQ )
{
	printf("AG_JoinTable_REQ\n");
	
	MSG_AG_JOINTABLE_REQ * pRecvMsg = (MSG_AG_JOINTABLE_REQ *)pMsg;
	DWORD dwUserKey = pRecvMsg->m_dwUserKey;
	BYTE byTableNumber = pRecvMsg->m_byTableNumber;
	
	GameUser * pUser = g_GameUserManager.Find(dwUserKey);
	if ( pUser == NULL ) {
		printf("Can't find User %d\n", dwUserKey);
		return;
	}
	pUser->SetTableNumber(byTableNumber);
	
	//m_pTableInfo[byTableNumber].m_szUserKey[0] = dwUserKey;
}

HANDLER_IMPL( AG_ShowCards_REQ )
{
	printf("AG_ShowCards_REQ\n");
	
}

HANDLER_IMPL( AG_Discards_BRD )
{
	printf("AG_Discards_BRD\n");
	
}

HANDLER_IMPL( AG_EndGame_SYN )
{
	printf("AG_EndGame_SYN\n");
}

HANDLER_IMPL( AG_InitCards_BRD )
{
	printf("AG_InitCards_BRD\n");
}
