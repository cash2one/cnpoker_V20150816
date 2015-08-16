#ifndef _LOGINUSERMANAGER_H_INCLUDED_
#define _LOGINUSERMANAGER_H_INCLUDED_

#include <Utility.h>
#include <Common.h>
#include <Network.h>
#include "ServerSession.h"
#include "LoginUser.h"


typedef std::map<DWORD, LoginUser*> 	MAP_LOGINUSER;
typedef MAP_LOGINUSER::iterator       	MAP_LOGINUSER_ITER;

class LoginUserManager : public A::Singleton<LoginUserManager>
{
public:
	LoginUserManager();
	virtual ~LoginUserManager();
	
	BOOL Init();
	
	void Release();
	
	void PUSH(LoginUser * pObj);
	LoginUser * POP(DWORD dwRootID);

private:
	MAP_LOGINUSER		m_mapLoginUser;
};

#endif // _USER_H_INCLUDED_
