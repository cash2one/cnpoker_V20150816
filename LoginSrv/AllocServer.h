#ifndef _ALLOCSERVER_H_INCLUDED_
#define _ALLOCSERVER_H_INCLUDED_

#include <Utility.h>
#include <Common.h>

#define FLOATSORT_ARRAY		(256)

class AllocServer : public Singleton<AllocServer>
{
public:
	AllocServer();
	~AllocServer();
	
	void Init(unsigned short _usMax);
	
	AgentServerSession * POP();
	
	void PUSH( AgentServerSession * pSession );
	
	unsigned char GetSize() const { return m_ucSize; }
	
public:
	unsigned short m_usMax;
	unsigned char  m_ucSize;
	AgentServerSession * m_sortArray[FLOATSORT_ARRAY];
};

#endif