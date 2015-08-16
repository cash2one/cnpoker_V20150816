#ifndef _AGENTSERVER_H_INCLUDED_
#define _AGENTSERVER_H_INCLUDED_

#include <Utility.h>
#include <Common.h>
#include <Network.h>
#include "AgentFactory.h"

using namespace std;

class AgentServer
{
	enum { CLIENT_SYNCHANDLER = 0, SERVER_SYNCHANDLER = 1, };
	
public:
	AgentServer(void);
	~AgentServer(void);

	BOOL Init();
	
	void StartServerSideListen();
	
	void StartClientSideListen();
	
	BOOL MaintainConnection();
	
	BOOL Update( DWORD dwDeltaTick );
	
	BOOL SendToGameServer( BYTE * pMsg, WORD wSize);
	ServerSession * GetGameServerSession() const;
	
	
private:
	BOOL 	m_bShutdown;
	IOCPServer * m_pIOCPServer;
	
	ServerSession * m_pGameServer;
	//ServerSession * m_pDBServer;
};

extern AgentServer * g_AgentServer;

#endif // _AGENTSERVER_H_INCLUDED_
