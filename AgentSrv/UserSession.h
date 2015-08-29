#ifndef _UserSession_H_INCLUDED_
#define _UserSession_H_INCLUDED_

#include <Utility.h>
#include <Common.h>
#include <Network.h>

#include "ServerSession.h"

enum eUSER_TYPE { UT_TEMP_USER, UT_USER };

class UserSession : public NetworkObject
{
public:
	UserSession();
	virtual ~UserSession();
	
	virtual void 	Init();
	virtual void 	Release();
	
	virtual BOOL SendPacket( BYTE *pMsg, WORD wSize );
	//virtual void SendClient(BYTE *pMsg, WORD wSize);
	//virtual void SendGame(BYTE *pMsg, WORD wSize);

	virtual eUSER_TYPE GetUserType() { return m_eUserType; }
	virtual void SetUserType(eUSER_TYPE eType) { m_eUserType = eType; }
	DWORD GetUserID() const;
	void  SetUserID( DWORD dwUserID );
	
	
protected:
	virtual void	OnAccept( DWORD dwNetworkIndex );
	virtual void	OnDisconnect();
	//virtual void	OnRecv(BYTE *pMsg, WORD wSize);
	//virtual void	OnConnect( BOOL bSuccess, DWORD dwNetworkIndex );
	virtual void	OnLogString( char * pszLog);

private:
	eUSER_TYPE 		m_eUserType; 	// 用户类型
	DWORD 			m_dwUserID; 	// User ID
	
	ServerSession * m_pNetGame;
};

#endif // _AGENTPLAYER_H_INCLUDED_
