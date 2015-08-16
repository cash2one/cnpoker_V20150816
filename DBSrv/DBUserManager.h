#ifndef _DBUSERMANAGER_H_INCLUDED_
#define _DBUSERMANAGER_H_INCLUDED_

#include <Utility.h>
#include <Common.h>
#include <Network.h>
#include "ServerSession.h"
#include "DBUser.h"

typedef std::map<DWORD, DBUser*> 	MAP_DBUSER;
typedef MAP_DBUSER::iterator       	MAP_DBUSER_ITER;

class DBUserManager : public A::Singleton<DBUserManager>
{
public:
	DBUserManager();
	virtual ~DBUserManager();
	
	BOOL Init();
	
	void Release();
	
	BOOL AddUser(DBUser * pUser);
	DBUser * Find(DWORD dwKey);
	BOOL Remove(DWORD dwKey);
	
private:
	MAP_DBUSER		m_mapDBUser;
};

#endif // _USER_H_INCLUDED_
