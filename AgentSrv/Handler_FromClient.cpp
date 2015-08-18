#include "Handler_FromClient.h"
#include "AgentServer.h"

using namespace std;

Handler_FromClient::Handler_FromClient() 
{
	
}

Handler_FromClient::~Handler_FromClient() 
{
	
}

HANDLER_IMPL( CA_Heartbeat_SYN )
{
	printf("CA_Heartbeat_SYN\n");
}

HANDLER_IMPL( CA_Prelogin_REQ )
{
	MSG_CA_PRELOGIN_GAME_REQ *pObj = (MSG_CA_PRELOGIN_GAME_REQ *)pMsg;
	
	MSG_AL_PRELOGIN_SYN msg2;
	msg2.m_dwParameter = pObj->m_dwParameter;
	memcpy(msg2.byUsername, pObj->byUsername, sizeof(pObj->byUsername) );
	memcpy(msg2.byPassword, pObj->byPassword, sizeof(pObj->byPassword) );
	g_AgentServer->SendToLoginServer( (BYTE *)&msg2, sizeof(msg2) );
}

HANDLER_IMPL( CA_Login_REQ)
{
	printf("CA_Login_REQ\n");
	MSG_CA_LOGIN_GAME_REQ * pObj = (MSG_CA_LOGIN_GAME_REQ *)pMsg;
	unsigned int uiRootID = pObj->m_uiRootID;
	printf("uiRootID = %d\n", uiRootID);
	
	MSG_AL_LOGIN_SYN msg2;
	msg2.m_dwParameter = pObj->m_dwParameter;
	msg2.uiRootID = pObj->m_uiRootID;
	memcpy(msg2.byUserKey, pObj->byUserKey, sizeof(pObj->byUserKey) );
	g_AgentServer->SendToLoginServer( (BYTE *)&msg2, sizeof(msg2) );
	
	/*
	MSG_AG_LOGIN_REQ msg2;
	msg2.m_uiRootID = uiRootID;	
	g_AgentServer->SendToGameServer( (BYTE *)&msg2, sizeof(msg2) );
	*/
}

HANDLER_IMPL( CA_Login_ANC)
{
	printf("CA_Login_ANC\n");
}

HANDLER_IMPL( CA_Logout_REQ)
{
	printf("CA_Logout_REQ\n");
}

HANDLER_IMPL( CA_Relogin_REQ )
{
	printf("CA_Relogin_REQ\n");
}


HANDLER_IMPL( CA_StartGame_REQ )
{
	// CA_StartGame_REQ: 301
	printf("1.CA_StartGame_REQ\n");
	printf("2.Send to GameServer: AG_Connect / AG_StartGame_REQ.\n");
	MSG_CA_START_GAME_REQ *pRecvMsg = (MSG_CA_START_GAME_REQ *)pMsg;
	DWORD dwUserID = pRecvMsg->m_dwParameter;
	
	// AG_START_GAME_REQ 
	MSG_AG_START_GAME_REQ msg2; // AG_Connect 10, AG_StartGame_REQ 2000
	msg2.m_dwParameter = dwUserID;
	printf("FromClient : UserKey->%d\n", msg2.m_dwParameter);
	
	g_AgentServer->SendToGameServer( (BYTE *)&msg2, sizeof(msg2) );
}

HANDLER_IMPL( CA_JoinRoom_REQ )
{
	printf("CA_JoinRoom_REQ Function\n");
	MSG_CA_JOINROOM_REQ *pRecvMsg = (MSG_CA_JOINROOM_REQ *)pMsg;
	DWORD dwUserID = pRecvMsg->m_dwParameter;
	printf("Room Number:%d\n", pRecvMsg->m_uiRoomNumber);
	
	MSG_AG_JOINROOM_REQ msg2;
	msg2.m_dwParameter = dwUserID; // User ID
	msg2.m_uiRoomNumber = pRecvMsg->m_uiRoomNumber; // Romm Number
	g_AgentServer->SendToGameServer( (BYTE *)&msg2, sizeof(msg2) );
}

HANDLER_IMPL( CA_JoinTable_REQ )
{
	printf("CA_JoinTable_REQ Function\n");
	
	MSG_CA_JOINTABLE_REQ *pRecvMsg = (MSG_CA_JOINTABLE_REQ *)pMsg;
	DWORD dwUserID = pRecvMsg->m_dwParameter;
	printf("Table Number:%d\n", pRecvMsg->m_uiTableNumber);
	
	MSG_AG_JOINTABLE_REQ msg2;
	msg2.m_dwParameter = dwUserID; // User ID
	msg2.m_uiTableNumber = pRecvMsg->m_uiTableNumber; // Table Number
	g_AgentServer->SendToGameServer( (BYTE *)&msg2, sizeof(msg2) );
}

HANDLER_IMPL( CA_ShowCards_REQ )
{
	printf("CA_ShowCards_REQ Function\n");
}

HANDLER_IMPL( CA_Discards_BRD )
{
	printf("CA_Discards_BRD Function\n");
}

HANDLER_IMPL( CA_EndGame_SYN )
{
	printf("CA_EndGame_SYN Function\n");
}

HANDLER_IMPL( CA_InitCards_BRD )
{
	printf("CA_InitCards_BRD Function\n");
}

