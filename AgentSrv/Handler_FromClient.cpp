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

HANDLER_IMPL( CA_PreLogin_REQ )
{
	printf("Step1: <1> CA_PreLogin_REQ\n");
	MSG_CA_PRELOGIN_REQ *pRecvMsg = (MSG_CA_PRELOGIN_REQ *)pMsg;
	
	MSG_AL_PRELOGIN_REQ msg2;
	msg2.m_dwParameter = pRecvMsg->m_dwParameter; // dwUserKey;
	memcpy(msg2.m_byUsername, pRecvMsg->m_byUsername, sizeof(pRecvMsg->m_byUsername) ); // 账户
	memcpy(msg2.m_byPassword, pRecvMsg->m_byPassword, sizeof(pRecvMsg->m_byPassword) ); // 密码
	g_AgentServer->SendToLoginServer( (BYTE *)&msg2, sizeof(msg2) );
}

HANDLER_IMPL( CA_Login_REQ)
{
	printf("Step2: <1> CA_Login_REQ\n");
	MSG_CA_LOGIN_REQ * pRecvMsg = (MSG_CA_LOGIN_REQ *)pMsg;
	unsigned int uiRootID = pRecvMsg->m_uiRootID;
	printf("uiRootID = %d\n", uiRootID);
	
	MSG_AL_LOGIN_REQ msg2;
	msg2.m_dwParameter = pRecvMsg->m_dwParameter;
	msg2.m_uiRootID = pRecvMsg->m_uiRootID;
	memcpy(msg2.m_byUserKey, pRecvMsg->m_byUserKey, sizeof(pRecvMsg->m_byUserKey) );
	g_AgentServer->SendToLoginServer( (BYTE *)&msg2, sizeof(msg2) );
}

HANDLER_IMPL( CA_ReLogin_REQ )
{
	printf("CA_Relogin_REQ\n");
}

HANDLER_IMPL( CA_Logout_REQ)
{
	printf("Logout: <1> CA_Logout_REQ\n");
	MSG_CA_LOGOUT_REQ * pRecvMsg = (MSG_CA_LOGOUT_REQ *)pMsg;
	
	MSG_AG_LOGOUT_REQ msg2;
	msg2.m_dwParameter = pRecvMsg->m_dwParameter;
	msg2.m_uiRootID = pRecvMsg->m_uiRootID;
	
	g_AgentServer->SendToGameServer( (BYTE *)&msg2, sizeof(msg2) );
}

/************************************************/

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

