#ifndef _POKER_H_INCLUDED_
#define _POKER_H_INCLUDED_

#include <Common.h>

class Poker
{
public:
	Poker(void);
	~Poker(void);

	static int Than(ePK_TYPE _my, char _myValue, char _myCount, ePK_TYPE _other, char _otherValue, char _otherCount);
	
	static int Pick(unsigned char * PK_Group, unsigned int PK_Size, char & thanValue, char & thanCount);
	
	static int OneTimes(unsigned char * szPK1, char iSizePK1, ePK_TYPE _other, char _otherValue, char _otherCount);
	//static int OneTimes(unsigned char * szPK1, char iSizePK1, unsigned char * szPK2, char iSizePK2);	
};



#endif // _POKER_H_INCLUDED_
