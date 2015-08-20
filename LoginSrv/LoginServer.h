#ifndef _LOGINSERVER_H_INCLUDED_
#define _LOGINSERVER_H_INCLUDED_

#include <Utility.h>
#include <Common.h>
#include <Network.h>
#include <Public.h>
#include "LoginFactory.h"

using namespace std;

class LoginServer
{
	enum { CLIENT_SYNCHANDLER = 0, SERVER_SYNCHANDLER = 1, };
	
public:
	LoginServer(void);
	~LoginServer(void);

	// 初始化
	BOOL Init();
	
	// 连接
	BOOL ConnectToServer( ServerSession * pSession, char * pszIP, WORD wPort );
	
	// 连接其他服务器
	BOOL MaintainConnection();
	
	// 更新帧
	BOOL Update( DWORD dwDeltaTick );
	
	// 释放
	//void Release();
		
	BOOL SendToAgentServer( BYTE * pMsg, WORD wSize );
	
	BOOL SendToDBServer( BYTE * pMsg, WORD wSize );
	
private:
	BOOL m_bShutdown;
	
	IOCPServer * m_pIOCPServer;
	
	//
	ServerSession * m_pDBServerSession;
	ServerSession * m_pAgentServerSession;
};

extern LoginServer * g_LoginServer;

#endif // _LOGINSERVER_H_INCLUDED_