#ifndef _DBSRV_TEST_H_INCLUDED_
#define _DBSRV_TEST_H_INCLUDED_

#include <Utility.h>
#include <Common.h>
#include <Network.h>

#include "ServerSession.h"

class DBSrv_Test: public ServerSession
{
public:
	DBSrv_Test();
	~DBSrv_Test();
	
	// 
	virtual void InitTest();
	virtual void ParsePacket(MSG_BASE * pMsg);

	void AutoTest();
	
	void LogInfo( BYTE *pMsg );
	
	void OnRecv( BYTE *pMsg, WORD wSize );
		
private:	
	int m_nStep;
	BOOL m_bRet;
	
	#if 0
	MSG_LD_LOGIN_SYN m_1;
	MSG_LD_LOGIN_ANC m_2;
	MSG_LD_LOGIN_SYN m_3;
	MSG_LD_LOGIN_ANC m_4;
	#endif


};

#endif // _DBSRV_TEST_H_INCLUDED_
