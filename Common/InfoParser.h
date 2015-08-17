#ifndef _INFOPARSER_H_INCLUDED_
#define _INFOPARSER_H_INCLUDED_

#include <Common.h>
#include <Network.h>
#include <Utility.h>
using namespace std;

struct SERVER_INFO
{
	char 	m_strIp[IP_MAX_LEN]; 	// IP
	DWORD 	m_dwPort; 		// PORT
	
	SERVER_INFO()
	{
		memset(this, 0, sizeof(SERVER_INFO));
		strcpy(m_strIp, "");
		m_dwPort = 0;		
	}	
};

class InfoParser
{
public:
	InfoParser(void);
	~InfoParser(void);

	// 初始化
	BOOL	Init(char * strFileName);

	BOOL	GetString( char * strSection, char * szName, char * szDefault, char *pszValue);
	int 	GetInt( char * strSection, char * szName, char * szDefault );

	// 获取服务器端口信息
	SERVER_INFO GetServerInfo(eSERVER_TYPE type);

private:
	Yond_ini * pIniFile;	
};

extern InfoParser g_InfoParser;

#endif // _INFOPARSER_H_INCLUDED_
