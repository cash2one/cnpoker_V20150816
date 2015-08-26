#ifndef _USER_H_INCLUDED_
#define _USER_H_INCLUDED_

#include <Utility.h>
#include <Common.h>
#include <Network.h>

#include "UserSession.h"

class User : public UserSession
{
public:
	User();
	virtual ~User();
	
	void Login();
	void Logout();
	
	BOOL IsOvertime();
	void Update();
		
	virtual void	OnAccept( DWORD dwNetworkIndex );
	virtual void	OnDisconnect();
	virtual void	OnRecv( BYTE *pMsg, WORD wSize );
	virtual void	OnConnect( BOOL bSuccess, DWORD dwNetworkIndex );
	
	BOOL SendPacket( BYTE *pMsg, WORD wSize );
	
};

#endif // _USER_H_INCLUDED_
