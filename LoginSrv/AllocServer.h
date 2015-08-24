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
	
	void Init(unsigned short _usMaxUser);
	
	AgentServerSession * POP();
	
	void PUSH( AgentServerSession * pSession );
	
	unsigned char GetSize() const { return m_ucSize; }
	
public:
	unsigned short m_usMax; 	// AgentServer 能接收最大用户数
	unsigned char  m_ucSize; 	// AgentServer 已分配数
	AgentServerSession * m_sortArray[FLOATSORT_ARRAY]; // 默认256个
};

#endif