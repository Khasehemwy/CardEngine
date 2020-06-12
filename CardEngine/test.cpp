#include"includes.h"

void Card_Game(GameModule* pGame)
{
	Card_SetTitle(pGame, "Test");

	Card_LoadImage("resources\\NieRAutomata-02-21-13-50-745.png","nier1");
	Card_PresentImage(pGame,"nier1");

	Card_MoveObject("nier1", 100, 10);
	Card_SetSizeObject("nier1", 1920/2, 1080/2);

}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) 
{
	GameModule* pGame = Card_Initial(hInstance);

	thread userThread(Card_Game, pGame);
	userThread.detach();


	Card_Run(pGame);

	return 0;
}

