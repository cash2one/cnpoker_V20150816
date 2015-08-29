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
	
	virtual eUSER_TYPE GetUserType() { return UT_TEMP_USER; }
	
	virtual void Init();
	virtual void Release(); // 释放函数
	
	BOOL DeCode( BYTE * pMsg, WORD wSize );
	
	
	
protected:
	virtual void	OnRecv( BYTE *pMsg, WORD wSize );
	virtual void	OnLogString( char * pszLog );
private:
	BOOL m_bFirst;
};

#endif // _AGENTPLAYER_H_INCLUDED_
