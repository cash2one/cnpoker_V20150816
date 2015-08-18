#ifndef _LOGINSERVERSESSION_H_INCLUDED_
#define _LOGINSERVERSESSION_H_INCLUDED_

#include <Utility.h>
#include <Common.h>
#include <Network.h>

#include "ServerSession.h"

class LoginServerSession : public ServerSession
{
public:
	LoginServerSession();
	virtual ~LoginServerSession();
	
	eSERVER_TYPE    GetServerType() { return LOGIN_SERVER; }
	
	virtual void    Init();
	
protected:
	virtual void	OnRecv(BYTE *pMsg, WORD wSize);
	virtual void	OnDisconnect();
	virtual void	OnLogString( char * pszLog);
};

#endif // _LOGINSERVERSESSION_H_INCLUDED_
