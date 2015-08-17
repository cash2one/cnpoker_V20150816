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

HANDLER_IMPL( CA_Login_REQ)
{
	printf("CA_Login_REQ\n");
	MSG_LOGIN *pLogin = (MSG_LOGIN *)pMsg;
	string a = pLogin->m_szBuffer;
	printf("Recv Buffer:%s\n", a.c_str());

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
	DWORD dwUserID = pRecvMsg->m_dwUserID;
	
	// AG_START_GAME_REQ 
	MSG_AG_START_GAME_REQ msg2; // AG_Connect 10, AG_StartGame_REQ 2000
	msg2.m_dwUserID = dwUserID;
	printf("FromClient : UserKey->%d\n", msg2.m_dwUserID);
	
	g_AgentServer->SendToGameServer( (BYTE *)&msg2, sizeof(msg2) );
}

HANDLER_IMPL( CA_JoinRoom_REQ )
{
	printf("CA_JoinRoom_REQ Function\n");
	MSG_CA_JOINROOM_REQ *pRecv = (MSG_CA_JOINROOM_REQ *)pMsg;
	printf("Room Number:%d\n", pRecv->m_byRoomNumber);
	
	MSG_AG_JOINROOM_REQ msg2;
	//msg2.m_dwUserID = dwUserID; // User ID
	msg2.m_byRoomNumber = pRecv->m_byRoomNumber; // Romm Number
	g_AgentServer->SendToGameServer( (BYTE *)&msg2, sizeof(msg2) );
}

HANDLER_IMPL( CA_JoinTable_REQ )
{
	printf("CA_JoinTable_REQ Function\n");
	
	MSG_CA_JOINTABLE_REQ *pRecv = (MSG_CA_JOINTABLE_REQ *)pMsg;
	printf("Table Number:%d\n", pRecv->m_byTableNumber);
	
	MSG_AG_JOINTABLE_REQ msg2;
	//msg2.m_dwUserID = dwUserID; // User ID
	msg2.m_byTableNumber = pRecv->m_byTableNumber; // Table Number
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

