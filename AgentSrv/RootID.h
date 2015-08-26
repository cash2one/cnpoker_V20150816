#ifndef _ROOT_ID_H_INCLUDED_
#define _ROOT_ID_H_INCLUDED_

#include <Utility.h>
#include <Common.h>


class RootID
{
public:
	RootID();
	virtual ~RootID();

	void Clear();
	
	//BYTE * GetUserKey() const;
	void SetUserKey( BYTE * pUserKey );
	BOOL IsSameUserKey( BYTE * pUserKey );
	
	DWORD GetRootID() const { return m_dwRootID; }
	void SetRootID( DWORD dwID ) { m_dwRootID = dwID; }

private:
	DWORD 	m_dwRootID;
	BYTE 	m_byUserKey[CODE_KEY_LEN + 1];
};

#endif // _ROOT_ID_H_INCLUDED_
