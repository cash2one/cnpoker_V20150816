#ifndef _LOGINUSER_H_INCLUDED_
#define _LOGINUSER_H_INCLUDED_

#include <Utility.h>
#include <Common.h>

class LoginUser
{
public:
	LoginUser();
	~LoginUser();

	void SetHashKey(DWORD dwKey) {	m_dwKey = dwKey; }
	DWORD GetHashKey() { return m_dwKey; }
	
	void SetRootID(DWORD dwRootID) {	m_dwRootID = dwRootID; }
	DWORD GetRootID() { return m_dwRootID; }
	
	void SetMD(BYTE * _md5);
	BOOL IsSameMD(BYTE * _md5);
	
private:
	DWORD  m_dwKey;
	DWORD  m_dwRootID;
	BYTE   m_byMD5[TICKET_LEN + 1];
};

#endif