#include"includes.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) 
{
	GameModule* pGame = Card_Initial(hInstance);
	Card_SetTitle(pGame, &(string)"Test");

	Card_Run(pGame);

	return 0;
}