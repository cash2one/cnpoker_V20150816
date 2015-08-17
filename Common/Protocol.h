#ifndef _PROTOCOL_H_INCLUDED_
#define _PROTOCOL_H_INCLUDED_

//--------------------------------------------------------------
/*
消息命名规则

1) (Request)						_REQ 请求消息
2) (Answer)							_ANS 应答消息
3) Client -> Server (Sync)			_SYN 同步消息
4) Server -> Client (Command)		-CMD 命令消息
5) Server -> Client Broadcasting	_BRD 广播消息
6) Server -> Client (Notify)		_NTF 服务器通知消息
7) 									_ACK 允许
8) 									_NAK 失败
*/
//--------------------------------------------------------------

enum eCategory_Type {
	/***** AG: Agent --> Game *****/
	AG_Connect 			= 10,
	AG_ClientLogin 		= 11,
	AG_Update 			= 12,
	
	/***** AL: Agent --> Login *****/
	AL_Connect 			= 20,
	AL_ClientLogin 		= 21,
	AL_Update 			= 22,
	
	/***** CA: Client --> Agent *****/
	CA_Connect 			= 30,
	CA_Client 	 		= 31,
	CA_Game 		 	= 32,
	
	/***** CL: Client --> Login *****/
	CL_Connect 			= 40,
	CL_ClientLogin 		= 41,	
	CL_Update 			= 42,
	
	/***** GD: GAME --> DB *****/
	GD_Connect 			= 50,
	GD_ClientLogin 		= 51,	
	GD_Update 			= 52,
	
	/***** LD: Login --> DB *****/
	LD_Connect 			= 60,
	LD_ClientLogin 		= 61,	
	LD_Update 			= 62,
};

#endif // _PROTOCOL_H_INCLUDED_
