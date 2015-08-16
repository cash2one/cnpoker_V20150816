#ifndef _DBUSER_H_INCLUDED_
#define _DBUSER_H_INCLUDED_

#include <Utility.h>
#include <Common.h>
#include <Network.h>


class DBUser
{
public:
	DBUser();
	virtual ~DBUser();

	void Login(unsigned int rootID);
	void Logout(unsigned int rootID);
	BOOL UpdateToDB();
	
	DWORD GetHashKey() const { return m_dwUserKey; }
	void SetHashKey( DWORD dwKey ) { m_dwUserKey = dwKey; }
	
	unsigned int GetRootID() const { return m_dwRootID; }
	void SetRootID( DWORD dwKey ) { m_dwRootID = dwKey; }
	
	GameInfo & GetGameInfo() { return m_sInfo; }
	
private:
	DWORD m_dwUpdateTime;    // Overtime 180 s;

	DWORD m_dwRootID;
	DWORD m_dwUserKey;
	DWORD m_dwLoginTime;     
	BYTE  m_szSSHkey[128];
	
	GameInfo m_sInfo;
	
	// char  m_szUsername[32];	
	// char  m_szPassword[32];	
};

#endif // _USER_H_INCLUDED_
