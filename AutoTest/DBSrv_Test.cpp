#include "DBSrv_Test.h"


DBSrv_Test::DBSrv_Test()
{
	
}

DBSrv_Test::~DBSrv_Test()
{
	
}

void DBSrv_Test::InitTest()
{
	
}

void DBSrv_Test::ParsePacket(MSG_BASE * pMsg)
{
	
}

void DBSrv_Test::AutoTest()
{
	
	#if 0
	if (Step == 0) {
		IsRet = FALSE; 	
		this->Send();
	}	
	if ( (Step == 0) && (IsRet == TRUE) ) {
		this->Send();	
	}
	#endif
}

void DBSrv_Test::LogInfo( BYTE *pMsg )
{
	int Step;
	int IsRet;
	
}


void DBSrv_Test::OnRecv( BYTE *pMsg, WORD wSize )
{
	//ParsePacket
}

