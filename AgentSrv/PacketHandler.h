#ifndef _PACKET_HANDLER_H_INCLUDED_
#define _PACKET_HANDLER_H_INCLUDED_

#include <Common.h>
#include <Network.h>
#include <Utility.h>
using namespace A;

#include "ServerSession.h"
#include "UserSession.h"

typedef VOID (*fnHandler)( ServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize );
typedef VOID (*fnHandler_c)( UserSession * pUserSession, MSG_BASE * pMsg, WORD wSize );

class PacketHandler
{
public:
	PacketHandler(void);
	~PacketHandler(void);

public:
	BOOL RegisterHandler();
	void Register_AG(); // Register_GA
	void Register_CA();
	void Register_AL(); // Register_LA
		
	BOOL AddHandler_CA( WORD category, WORD protocol, fnHandler_c fnHandler);
	BOOL AddHandler_AG( WORD category, WORD protocol, fnHandler fnHandler);
	BOOL AddHandler_AL( WORD category, WORD protocol, fnHandler fnHandler);
	
	void ParsePacket_CA( UserSession * pUserSession, MSG_BASE * pMsg, WORD wSize );
	void ParsePacket_AG( ServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize );
	void ParsePacket_AL( ServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize );

private:
	struct FUNC_CA : public BASE_FUNC
	{
		fnHandler_c	m_fnHandler;
	};

	struct FUNC_AG : public BASE_FUNC
	{
		fnHandler	m_fnHandler;
	};
	
	struct FUNC_AL : public BASE_FUNC
	{
		fnHandler	m_fnHandler;
	};

	FunctionMap	*	m_pFuncMap_AG;
	FunctionMap	*	m_pFuncMap_CA;
	FunctionMap	*	m_pFuncMap_AL;		
};

extern PacketHandler g_PacketHandler;

#endif
