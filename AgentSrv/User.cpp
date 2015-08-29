#include "User.h"

#include "PacketHandler.h"

#include "AgentFactory.h"
#include "UserManager.h"
#include "RootidManager.h"

User::User()
	: m_uiRootID(0)
{	
	//m_pUserSession = NULL;
	//m_pGameSession = NULL;
}

User::~User()
{
}

void User::Init()
{
	UserSession::Init();
}

void User::Release()
{
	printf("[User::Release] \n");
	DWORD dwUserID = GetUserID();
	printf("User Key:%d, Num counts =%d\n", dwUserID, g_UserManager.GetUserNums());
	g_UserManager.Remove( dwUserID );
	
	printf("AgentFactory::Instance()->FreeUser() : %d\n", dwUserID);
	AgentFactory::Instance()->FreeUser(this);
			
	RootID * pRoot = RootidManager::Instance()->FindRootID( m_uiRootID );
	if ( pRoot != NULL ) {
		printf("AgentFactory::Instance()->FreeRootID() : %d\n", m_uiRootID);
		AgentFactory::Instance()->FreeRootID( pRoot );
		
		printf("RootidManager::Instance()->RemoveRootID() : %d Success.\n", m_uiRootID);
		RootidManager::Instance()->RemoveRootID( m_uiRootID );
		return;
	}
	printf("Error: RootidManager::Instance()->FindRootID(%d) Fail.\n", m_uiRootID);
}

BOOL User::SendPacket( BYTE *pMsg, WORD wSize )
{
	return UserSession::SendPacket( pMsg, wSize );
}

/****************************************************/
void User::Login()
{
}

void User::Logout()
{
}

void User::Update()
{
	
}

BOOL User::IsOvertime()
{
	
}

void User::OnAccept( DWORD dwNetworkIndex )
{
	
}

void User::OnDisconnect()
{
	
}

void User::OnRecv(BYTE *pMsg, WORD wSize)
{
	printf("User OnRecv --> MSG:%s,size:%d\n", (char *)pMsg, wSize);
	printf("call g_PacketHandler.ParsePacket_CA Function.\n");
	g_PacketHandler.ParsePacket_CA(this, (MSG_BASE *)pMsg, wSize);	
}

void User::OnConnect( BOOL bSuccess, DWORD dwNetworkIndex )
{
	
}
