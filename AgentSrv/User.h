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
	
	void Login();
	void Logout();
	
	BOOL IsOvertime();
	void Update();
	
	virtual void	OnAccept( DWORD dwNetworkIndex );
	virtual void	OnDisconnect();
	virtual void	OnRecv( BYTE *pMsg, WORD wSize );
	virtual void	OnConnect( BOOL bSuccess, DWORD dwNetworkIndex );
	
	BOOL SendPacket( BYTE *pMsg, WORD wSize );
	
private:
	//UserSession * m_pUserSession;
	//GameServerSession * m_pGameSession;
	
	WORD  m_dwOvertime;    // Overtime 180 s;
	DWORD m_dwLeave;

	// User Info
	DWORD m_dwUserID;
	std::string m_strUserName;
	std::string m_strPassword;
	float m_fMoney;
	std::string m_strDynamicID;
	
	PlayerInfo m_pPlayer;
	#if 0
	char m_szUserKey; 		// 用户的Key
	uint m_uiDBUserID; 		// 用户数据库ID
	uint m_uiMoney; 		// 拥有的钱
	uint m_uiPrepaid; 		// 预付的钱
	float m_fWonRate; 		// 胜率
	float m_fEscapeRate; 	// 逃跑率
	uint m_uiRankList; 		// 排行
	uint m_uiGoodsList[5]; 	// 道具
	#endif
};

#endif // _USER_H_INCLUDED_
