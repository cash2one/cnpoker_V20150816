#include "LoginServer.h"

int main(int argc, char ** argv) 
{
	g_LoginServer = new LoginServer;
	g_LoginServer->Init();
	
	while(true) {
		Sleep(100);
		g_LoginServer->Update(0);
	}
	
	return 0;
}