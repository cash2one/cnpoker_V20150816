#include "AgentServerSession.h"
#include "AllocServer.h"

AllocServer::AllocServer()
{
	m_ucSize = 0;
	memset( m_sortArray, 0x0, FLOATSORT_ARRAY ); 
}

AllocServer::~AllocServer()
{
	
}

void AllocServer::Init(unsigned short _usMax)
{
	m_usMax = _usMax;
}

AgentServerSession * AllocServer::POP()
{
	if ( m_ucSize != 0 )
	{
		for ( int i=0; i < m_ucSize; ++i )
		{
			if ( m_sortArray[i]->m_userCount < m_usMax )
			{
				return m_sortArray[m_ucSize];
			}
		}
	}
	return NULL;
}
	
void AllocServer::PUSH( AgentServerSession * pSession )
{
	if ( m_ucSize < FLOATSORT_ARRAY )
	{
		++m_ucSize;
		m_sortArray[m_ucSize] = pSession;
	}
}