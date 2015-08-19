#ifndef _POKER_H_INCLUDED_
#define _POKER_H_INCLUDED_

#include <Common.h>

class Poker
{
public:
	Poker(void);
	~Poker(void);

	static int Than(ePK_TYPE _my, char _myValue, char _myCount, ePK_TYPE _other, char _otherValue, char _otherCount);
	
	static int Pick(char * PK_Group, char PK_Size, char & thanValue, char & thanCount);
	
	static int OneTimes(char * szPK1, char iSizePK1, char * szPK2, char iSizePK2);	
};



#endif // _POKER_H_INCLUDED_
