#include"CardEngine.h"


SDL_Event* pEvent;

Image background1_image("background1_image");
GameObject background1("background1");

Image Fireworks_image("Fireworks_image");
GameObject Fireworks("Fireworks");

Image char1_idle("char1_idle");
Image char1_walk("char1_walk");
GameObject char1("char1");


SDL_RendererFlip flip;

void Move()
{

	if (pEvent->type == SDL_KEYDOWN) {
		switch (pEvent->key.keysym.sym)
		{
		case SDLK_RIGHT:
			char1.ChooseAnimation(char1_walk);
			flip = SDL_FLIP_NONE;
			char1.SetPosition(char1.rect.x + 4, char1.rect.y);
			break;
		case SDLK_LEFT:
			char1.ChooseAnimation(char1_walk, SDL_FLIP_HORIZONTAL);
			flip = SDL_FLIP_HORIZONTAL;
			char1.SetPosition(char1.rect.x - 4, char1.rect.y);
			break;
		}
	}
	else {
		char1.ChooseAnimation(char1_idle, flip);
	}
}


void Card_Update(EngineModule* pGame)
{
	Move();

}


void Card_Start(EngineModule* pGame)
{
	pEvent = Card_GetEvent();
	Card_SetTitle(pGame, "Move");

	background1_image.Load("resources\\background\\background1.png");
	background1.AddImage(background1_image);
	background1.Present();

	background1.SetSize(_Card_Size_FullWindow);
	background1.ChooseAnimation(background1_image, SDL_FLIP_HORIZONTAL);


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
	//char1.SetAnimationLoop(char1_idle,FALSE);


	char1.SetSize(5);
	char1.SetPosition(100, 1100);
	char1.SetDatumPoint(_Card_DatumPoint_BottomLeft);
	char1.SetAnimationSpeed(1.1);
	char1.SetImageAlpha(255);
}