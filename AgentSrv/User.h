#ifndef _USER_H_INCLUDED_
#define _USER_H_INCLUDED_

#include <Utility.h>
#include <Common.h>
#include <Network.h>

#include "UserSession.h"
//#include "GameServerSession.h"

class User : public UserSession
{
public:
	User();
	virtual ~User();

	virtual eUSER_TYPE GetUserType() { return UT_USER; }
	
	virtual void Init();
	virtual void Release(); // 释放函数
	
	virtual BOOL SendPacket( BYTE *pMsg, WORD wSize );
	
	void SetRootID( DWORD dwRootid ) { m_uiRootID = dwRootid; }

	//
	void Login();
	void Logout();
	
	BOOL IsOvertime();
	void Update();
	
protected:	
	virtual void	OnAccept( DWORD dwNetworkIndex );
	virtual void	OnDisconnect();
	virtual void	OnRecv( BYTE *pMsg, WORD wSize );
	virtual void	OnConnect( BOOL bSuccess, DWORD dwNetworkIndex );
	
private:
	DWORD m_uiRootID;
};

#endif // _USER_H_INCLUDED_
