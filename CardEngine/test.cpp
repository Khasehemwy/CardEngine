#include"includes.h"


SDL_Event* pEvent;

Image nier1("nier1");

GameObject char1("char1");
Image char1_idle("char1_idle");
Image char1_walk("char1_walk");

SDL_RendererFlip flip;

void Move()
{

	if (pEvent->type == SDL_KEYDOWN) {
		switch (pEvent->key.keysym.sym)
		{
		case SDLK_RIGHT: 
			char1.ChooseAnimation(char1_walk);
			flip = SDL_FLIP_NONE;
			char1.SetPosition(char1.rect.x + 10, char1.rect.y);
			break;
		case SDLK_LEFT:
			char1.ChooseAnimation(char1_walk, SDL_FLIP_HORIZONTAL);
			flip = SDL_FLIP_HORIZONTAL;
			char1.SetPosition(char1.rect.x - 10, char1.rect.y);
			break;
		}
	}
	else {
		char1.ChooseAnimation(char1_idle, flip);
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

	char1_idle.Load("resources\\char\\PixelCharAnim_Plain_idle1.png");
	char1_idle.Load("resources\\char\\PixelCharAnim_Plain_idle2.png");
	char1_idle.Load("resources\\char\\PixelCharAnim_Plain_idle3.png");
	char1_idle.Load("resources\\char\\PixelCharAnim_Plain_idle4.png");

	char1_walk.Load("Resources\\Char\\run\\PixelCharAnim_Plain_run1.png");
	char1_walk.Load("Resources\\Char\\run\\PixelCharAnim_Plain_run2.png");
	char1_walk.Load("Resources\\Char\\run\\PixelCharAnim_Plain_run3.png");
	char1_walk.Load("Resources\\Char\\run\\PixelCharAnim_Plain_run4.png");
	char1_walk.Load("Resources\\Char\\run\\PixelCharAnim_Plain_run5.png");
	char1_walk.Load("Resources\\Char\\run\\PixelCharAnim_Plain_run6.png");

	char1.AddImage(char1_idle);
	char1.AddImage(char1_walk);
	char1.Present();
	//nier1.Present();


	
	char1.SetSize(10);
	char1.SetPosition(100, 100);
	char1.SetDatumPoint(_Card_DatumPoint_BottomLeft);
	char1.SetAnimationSpeed(2);
	char1.SetImageAlpha(100);

}





