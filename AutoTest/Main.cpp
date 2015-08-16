#include "AutoTest.h"

int main()
{
	g_AutoTest = new AutoTest;
	g_AutoTest->Init();
	
	char buf[32] = {0};
	while(true) {
		Sleep(100);
		
		printf("\n**************** CMD List ****************\n");
		printf(">>>>GameServer\n");
		printf("1.Send GD_Login_SYN\n");
		printf("2.Send GD_Logout_SYN\n");
		printf("3.Send GD_Save_CMD\n");
		printf("4.Send GD_Update_CMD\n");
		printf(">>>>LoginServer\n");
		printf("5.Send GD_Login_SYN\n");
		printf("6.Send GD_Logout_SYN\n");
		printf("7.Send GD_Save_CMD\n");
		printf("8.Send GD_Update_CMD\n");
		printf("\n**************** CMD List ****************\n");
		
		memset(buf, 0, 32);
		fgets(buf, sizeof(buf), stdin);
		int nChoice = atoi(buf);
		printf("Select MSG:%d\n", nChoice);
		
		g_AutoTest->Update(nChoice);
	}
	
	return 0;
}