#include "Handler_FromAgentServer.h"

#include "GameServer.h"
#include "GameUserManager.h"

Handler_FromAgentServer::Handler_FromAgentServer() 
{
	
}

Handler_FromAgentServer::~Handler_FromAgentServer() 
{
	
}

HANDLER_IMPL( AG_Login_REQ )
{
	printf("AG_Login_REQ\n");
	MSG_AG_LOGIN_REQ * pRecvMsg = (MSG_AG_LOGIN_REQ *)pMsg;
	unsigned int uiRootID = pRecvMsg->m_uiRootID;
	printf("uiRootID = %d\n", uiRootID);
	
	MSG_GD_LOGIN_SYN msg2;
	msg2.m_dwParameter = pRecvMsg->m_dwParameter;
	msg2.uiRootID = uiRootID;
	
	//g_GameServer->SendToDBServer( (BYTE *)&msg2, sizeof(msg2) );
}

HANDLER_IMPL( AG_StartGame_REQ )
{
	printf("AG_StartGame_REQ\n");
	
	MSG_AG_START_GAME_REQ * pRecvMsg = (MSG_AG_START_GAME_REQ *)pMsg;
	DWORD dwUserID = pRecvMsg->m_dwParameter;
	
	// 先查找用户
	GameUser * pUser = g_GameUserManager.Find(dwUserID);
	//pUser->StartGame(); // Do nothing
	
	// 返回应答数据给Agent
	MSG_AG_START_GAME_ANC msg2;
	msg2.m_dwParameter = dwUserID;
	
	g_GameServer->SendToAgentServer( (BYTE *)&msg2, sizeof(msg2) );
}

HANDLER_IMPL( AG_JoinRoom_REQ )
{
	printf("AG_JoinRoom_REQ\n");
	
	MSG_AG_JOINROOM_REQ * pRecvMsg = (MSG_AG_JOINROOM_REQ *)pMsg;
	DWORD dwUserID = pRecvMsg->m_dwParameter;
	unsigned int uiRoomNumber = pRecvMsg->m_uiRoomNumber;
	
	GameUser * pUser = g_GameUserManager.Find(dwUserID);
	if ( pUser == NULL ) {
		printf("Can't find User %d\n", dwUserID);
		return;
	}
	pUser->SetRoomNumber(uiRoomNumber);

	// 回复 AG_JoinRoom_ANC 信息
	//MSG_AG_JOINROOM_ANC msg2;
	//g_GameServer->SendToAgentServer( (BYTE *)&msg2, sizeof(msg2) );
}

HANDLER_IMPL( AG_JoinTable_REQ )
{
	printf("AG_JoinTable_REQ\n");
	
	MSG_AG_JOINTABLE_REQ * pRecvMsg = (MSG_AG_JOINTABLE_REQ *)pMsg;
	DWORD dwUserID = pRecvMsg->m_dwParameter;
	unsigned int uiTableNumber = pRecvMsg->m_uiTableNumber;
	//unsigned int uiSeat = pRecvMsg->m_uiSeat;
	
	GameUser * pUser = g_GameUserManager.Find(dwUserID);
	if ( pUser == NULL ) {
		printf("Can't find User %d\n", dwUserID);
		return;
	}
	pUser->SetTableNumber(uiTableNumber);
	
	for(int i=0; i<3; ++i)
	{
		if( pUser->m_TableInfo[uiTableNumber].m_uiUserKey[i] == 0 ) {
			pUser->m_TableInfo[uiTableNumber].m_uiUserKey[i] = dwUserID;
			pUser->SetSeat(i); // 设置座位
			break;
		}
	}
	
	// 回复 AG_JoinTable_ANC 信息
	//MSG_AG_JOINTABLE_ANC msg2;
	//g_GameServer->SendToAgentServer( (BYTE *)&msg2, sizeof(msg2) );
}

HANDLER_IMPL( AG_InitCards_BRD )
{
	printf("AG_InitCards_BRD\n");
	
	MSG_AG_INITCARDS_BRD * pRecvMsg = (MSG_AG_INITCARDS_BRD *)pMsg;
	DWORD dwUserID = pRecvMsg->m_dwParameter;
	
	GameUser * pUser = g_GameUserManager.Find(dwUserID);
	if ( pUser == NULL ) {
		printf("Can't find User %d\n", dwUserID);
		return;
	}
	pUser->InitCards(); // 牌已经分为3份。 只是把牌分为3份，但不知道牌是什么。
	pUser->AllocCards(); // 获得自己的牌, 其他用户的牌也一起分了
	
#if 1
	// 把另外2份牌发送给其他2个User
	GameUser * pFirst = pUser;
	for(int i=0; i<2; ++i) {
		GameUser * pNextUser = pFirst->GetNextGameUser();
		pNextUser->AllocCards(); // 把牌分给对应的人。 牌出来了。
		pFirst = pNextUser;	
	}
#endif
	
	// 返回 消息包 给 Agent
	MSG_AG_INITCARDS_ANC msg2;
	msg2.m_byParameter = dwUserID;
	g_GameServer->SendToAgentServer( (BYTE *)&msg2, sizeof(msg2) );
}

HANDLER_IMPL( AG_ShowCards_REQ )
{
	printf("AG_ShowCards_REQ\n");
	
	MSG_AG_SHOWCARDS_REQ * pRecvMsg = (MSG_AG_SHOWCARDS_REQ *)pMsg;
	DWORD dwUserID = pRecvMsg->m_dwParameter;
	
	GameUser * pUser = g_GameUserManager.Find(dwUserID);
	if ( pUser == NULL ) {
		printf("Can't find User %d\n", dwUserID);
		return;
	}
	pUser->ShowCards();
}

HANDLER_IMPL( AG_Discards_REQ )
{
	printf("AG_Discards_REQ\n");
	
	MSG_AG_DISCARDS_REQ * pRecvMsg = (MSG_AG_DISCARDS_REQ *) pMsg;
	DWORD dwUserID = pRecvMsg->m_dwParameter;
	
	GameUser * pUser = g_GameUserManager.Find(dwUserID);
	if ( pUser == NULL ) {
		printf("Can't find User %d\n", dwUserID);
		return;
	}
	pUser->Discards(pRecvMsg->m_byDiscards, pRecvMsg->m_uiSize);
	
	// 手上牌已打完，取得胜利
	if ( pUser->IsWinTheGame() ) {
		MSG_AG_WINPLAYER_BRD msg2;
		msg2.m_dwParameter = dwUserID;
		
		g_GameServer->SendToAgentServer( (BYTE *)&msg2, sizeof(msg2) );
	}
}

HANDLER_IMPL( AG_EndGame_SYN )
{
	printf("AG_EndGame_SYN\n");
}

