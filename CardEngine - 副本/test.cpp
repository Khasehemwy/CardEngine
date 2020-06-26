#include"includes.h"


SDL_Event* pEvent;

Image nier1("nier1");
Image char1("char1");


void Move()
{
	if (pEvent->type == SDL_KEYDOWN && pEvent->key.keysym.sym == SDLK_RIGHT) {
		char1.SetPosition(char1.rect.x + 10,char1.rect.y);
	}
}


void Card_Update(GameModule* pGame)
{
	Move();
}


void Card_Start(GameModule* pGame)
{
	pEvent = Card_GetEvent();
	Card_SetTitle(pGame, "Test");

	nier1.Load("resources\\NieRAutomata1.png");
	/*Card_LoadImage("resources\\NieRAutomata1.png")*/

	char1.Load("resources\\char\\PixelCharAnim_Plain_idle1.png");
	char1.Load("resources\\char\\PixelCharAnim_Plain_idle2.png");
	char1.Load("resources\\char\\PixelCharAnim_Plain_idle3.png");
	char1.Load("resources\\char\\PixelCharAnim_Plain_idle4.png");	

	char1.Present();
	//nier1.Present();

	//Image char2 = char1;
	//char2.Present();
	//char2.SetPosition(300, 300);
	
	char1.SetSize(20);
	char1.SetPosition(100, 100);
	char1.SetDatumPoint(_Card_BottomLeft);
	char1.SetAlpha(100);
	char1.SetAnimationSpeed(3);

	//char1.SetPosition(200, 200);
}





