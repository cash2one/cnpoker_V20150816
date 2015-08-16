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
	printf("------>Handler Impl CA Heartbeat SYN\n");
}

HANDLER_IMPL( CA_Login_REQ)
{
	printf("------>Handler Impl CA Login REQ\n");
	MSG_LOGIN *pLogin = (MSG_LOGIN *)pMsg;
	string a = pLogin->m_szBuffer;
	printf("Recv Buffer:%s\n", a.c_str());

//	string backString = "";
}

HANDLER_IMPL( CA_Login_ANC)
{
	printf("------>Handler Impl CA Login ANC\n");
}

HANDLER_IMPL( CA_Logout_REQ)
{
	printf("------>Handler Impl CA Logout REQ\n");
}

HANDLER_IMPL( CA_Relogin_REQ )
{
	printf("------>Handler Impl CA Relogin REQ\n");
}


HANDLER_IMPL( CA_StartGame_REQ )
{
	// CA_StartGame_REQ: 301
	printf("------>Handler Client--> Agent StartGame REQ\n");
	printf("------>Send to GameServer: GA_Connect / GA_StartGame_REQ.\n");
	MSG_CA_START_GAME_REQ *pRecvMsg = (MSG_CA_START_GAME_REQ *)pMsg;
	//DWORD dwUserKey = pRecvMsg->m_dwUserKey;
	
	MSG_GA_START_GAME_REQ msg2; // GA_Connect 40, GA_StartGame_REQ 2000
	msg2.m_dwUserKey = pRecvMsg->m_dwUserKey;
	printf("FromClient : UserKey->%d\n", msg2.m_dwUserKey);
	
	g_AgentServer->SendToGameServer( (BYTE *)&msg2, sizeof(msg2) );
}

#if 0
HANDLER_IMPL( CA_JoinRoom_REQ )
{
	
}

HANDLER_IMPL( CA_JoinTable_REQ )
{
	
}

HANDLER_IMPL( CA_ShowCards_REQ )
{
	
}

HANDLER_IMPL( CA_Discards_REQ )
{
	
}

HANDLER_IMPL( CA_EndGame_REQ )
{
		
}
#endif
