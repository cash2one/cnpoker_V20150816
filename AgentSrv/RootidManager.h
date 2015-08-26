#ifndef _ROOT_ID_MANAGER_H_INCLUDED_
#define _ROOT_ID_MANAGER_H_INCLUDED_

#include <Utility.h>
#include <Common.h>

#include "RootID.h"

typedef std::map<DWORD, RootID *> 	MAP_ROOTID;
typedef MAP_ROOTID::iterator       	MAP_ROOTID_ITER;

class RootidManager : public A::Singleton<RootidManager>
{
public:
	RootidManager();
	virtual ~RootidManager();
	
	BOOL Init();
	
	void Release();
	
	BOOL AddRootID( RootID * pRoot );
	RootID * FindRootID( const DWORD dwRootID );
	BOOL RemoveRootID( const DWORD dwRootID );
	
private:
	MAP_ROOTID		m_mapRootid;
};

extern RootidManager g_RootidManager;

#endif // _ROOT_ID_MANAGER_H_INCLUDED_

