#include"CardEngine.h"

Image fireworks_image("fireworks_image");
GameObject fireworks("fireworks");

SDL_Event* pEvent;

int jug = 0;
void Card_Update(EngineModule* pGame)
{
	if (pEvent->type == SDL_MOUSEBUTTONDOWN && jug == 0) {
		//fireworks.Present();
		fireworks.SetPosition(pEvent->button.x - fireworks.rect.w / 2, pEvent->button.y - fireworks.rect.h / 2);
		fireworks.SetAnimationReplay(fireworks_image);
		fireworks.SetImageAlpha(255);
		jug = 1;
	}
	else if (pEvent->type == SDL_MOUSEBUTTONUP) { jug = 0; }
	if (fireworks.GetAnimationEndState(fireworks_image) == TRUE) {
		fireworks.SetImageAlpha(0);
	}
}

void Card_Start(EngineModule* pGame)
{
	Card_SetTitle(pGame, "Fireworks");
	pEvent = Card_GetEvent();

	fireworks_image.Load("resources\\fireworks\\tx_yanhua_000.png");
	fireworks_image.Load("resources\\fireworks\\tx_yanhua_001.png");
	fireworks_image.Load("resources\\fireworks\\tx_yanhua_002.png");
	fireworks_image.Load("resources\\fireworks\\tx_yanhua_003.png");
	fireworks_image.Load("resources\\fireworks\\tx_yanhua_004.png");
	fireworks_image.Load("resources\\fireworks\\tx_yanhua_005.png");
	fireworks_image.Load("resources\\fireworks\\tx_yanhua_006.png");
	fireworks_image.Load("resources\\fireworks\\tx_yanhua_007.png");
	fireworks_image.Load("resources\\fireworks\\tx_yanhua_008.png");
	fireworks_image.Load("resources\\fireworks\\tx_yanhua_009.png");
	fireworks_image.Load("resources\\fireworks\\tx_yanhua_010.png");
	fireworks_image.Load("resources\\fireworks\\tx_yanhua_011.png");
	fireworks_image.Load("resources\\fireworks\\tx_yanhua_012.png");
	fireworks_image.Load("resources\\fireworks\\tx_yanhua_013.png");
	fireworks_image.Load("resources\\fireworks\\tx_yanhua_014.png");
	fireworks_image.Load("resources\\fireworks\\tx_yanhua_015.png");

	fireworks.AddImage(fireworks_image);
	fireworks.Present();

	fireworks.SetImageAlpha(0);
	fireworks.SetDatumPoint(_Card_DatumPoint_Center);
	fireworks.SetPosition(300, 300);
	fireworks.SetAnimationSpeed(1.4);
	fireworks.SetSize(1);
	fireworks.SetAnimationLoop(fireworks_image, FALSE);
}