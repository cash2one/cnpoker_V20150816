#ifndef _TempUserSession_H_INCLUDED_
#define _TempUserSession_H_INCLUDED_

#include <Utility.h>
#include <Common.h>
#include <Network.h>
#include "UserSession.h"

class TempUserSession : public UserSession
{
public:
	TempUserSession();
	virtual ~TempUserSession();
	
	virtual void Init(void);
	virtual void Release(void);
	
	BOOL DeCode( BYTE * pMsg, WORD wSize );
	
public:
	virtual void	OnRecv( BYTE *pMsg, WORD wSize );
	virtual void	OnLogString( char * pszLog );
};

#endif // _AGENTPLAYER_H_INCLUDED_
