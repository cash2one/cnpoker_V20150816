#ifndef _USERMANAGER_H_INCLUDED_
#define _USERMANAGER_H_INCLUDED_

#include <Utility.h>
#include <ObjKeyGenerator.h>

class User;
class UserSession;
//class UserFactory;

typedef hash_map<DWORD, User *>					USER_AUTH_IDS;
typedef hash_map<std::string, User *>			M_USER_LIST;
typedef std::pair<std::string, User *>			M_USER_LIST_PAIR;

class UserManager
{
public:
	UserManager();
	~UserManager();

	void InitUserSize( DWORD dwUserSize );
	DWORD AddUser( User * pUser ); // UserSession -> key HashTable
	DWORD GetUserNums();
	User * FindUser( DWORD dwKey ); // 
	void Remove( DWORD dwKey ); // HashTable
	void Remove( User * pUser ); 
	// 分配一个用户KEY
	DWORD AllocKey() {  return m_UserKey.GetKey(); }
	
private:
	CObjKeyGenerator							m_UserKey;
	A::SolarHashTable<User *> *					m_pUserHashTable;
	USER_AUTH_IDS								m_UserAuthIDs;
	M_USER_LIST									m_CharNameHashTable;
	
};

extern UserManager g_UserManager;

#endif // _USERMANAGER_H_INCLUDED_

