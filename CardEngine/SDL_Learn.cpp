#include"includes.h"

void Card_HandleEvent(SDL_Event* evt, SDL_Renderer* pRender, queue<SDL_Texture*>* listTexture);
int PlayMusic(const wchar_t* Cmd);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR lpCmdLine, int nCmdShow)
{
	//Card_Initial
	int ret = SDL_Init(SDL_INIT_EVERYTHING);
	if (ret < 0) { return -1; }
	queue<SDL_Texture*>listTexture;

	//create window
	string title = "ssas";
	const char* title2;
	title2 = title.c_str();
	SDL_Window* pWin = SDL_CreateWindow(title2, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
	if (pWin == NULL) { return -2; }

	//creat render
	SDL_Renderer* pRenderer = SDL_CreateRenderer(pWin, -1, SDL_RENDERER_ACCELERATED);
	if (pRenderer == NULL) {
		SDL_DestroyWindow(pWin);
		return -3;
	}
	SDL_SetRenderDrawColor(pRenderer, 220, 220, 220, 255);
	SDL_RenderClear(pRenderer);
	SDL_RenderPresent(pRenderer);


	//load png image
	//if (IMG_Init(IMG_INIT_PNG) == -1)return -1;
	SDL_Surface* pImageSurface = IMG_Load("Resources\\LISA.png");
	if (pImageSurface == NULL) { SDL_Log("Load image failed.\n%s", SDL_GetError()); return -1; }

	SDL_Texture* pImageTexture = SDL_CreateTextureFromSurface(pRenderer, pImageSurface);
	listTexture.push(pImageTexture);
	//SDL_RenderCopy(pRenderer, pImageTexture, NULL, NULL);
	//SDL_RenderPresent(pRenderer);


	//load ttf
	if (TTF_Init() == -1)return -1;
	SDL_Color FontColor = { 19,53,71,255 };
	TTF_Font* pFont = TTF_OpenFont("Resources\\Zpix.ttf", 24);

	SDL_Surface* pFontSurface = TTF_RenderText_Blended(pFont, "Are you OK???", FontColor);
	if (pFontSurface == NULL) { SDL_Log("Load font failed.\n%s", SDL_GetError()); return -1; }
	SDL_Texture* pFontTexture = SDL_CreateTextureFromSurface(pRenderer, pFontSurface);

	SDL_Rect FontRect;
	FontRect.x = 100; FontRect.y = 100; FontRect.w = 400; FontRect.h = 80;

	listTexture.push(pFontTexture);


	//load music
	//mciSendString(TEXT("open Resources\\can_loop_update.mp3 type mpegvideo"), NULL, 0, NULL);
	//ret = PlayMusic(TEXT("play Resources\\can_loop_update.mp3"));
	//ret = mciSendString(TEXT("play Resources\\can_loop_update.mp3 repeat"), NULL, 0, NULL);
	//if (ret != 0) { SDL_Log("Load music failed.\n"); }
	//mciSendString(TEXT("setaudio Resources\\can_loop_update.mp3 volume to 200"), NULL, 0, NULL);
	Mix_Init(MIX_INIT_MP3);
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048);
	Mix_Chunk* pMusic = Mix_LoadWAV("Resources\\can_loop_update.mp3");
	Mix_PlayChannel(-1,pMusic, -1);



	//handle events
	SDL_Event evt;
	Card_HandleEvent(&evt,pRenderer,&listTexture);



	//quit
	if (pFontSurface) { SDL_FreeSurface(pFontSurface); }
	if (pImageSurface) { SDL_FreeSurface(pImageSurface); }
	if (pFontTexture) { SDL_DestroyTexture(pFontTexture); }
	if (pImageTexture) { SDL_DestroyTexture(pImageTexture); }
	if (pRenderer) { SDL_DestroyRenderer(pRenderer); }
	if (pWin) { SDL_DestroyWindow(pWin); }
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();

	return 0;
}

void Card_HandleEvent(SDL_Event* pEvt, SDL_Renderer* pRender, queue<SDL_Texture*>* listTexture)
{
	BOOL quit = FALSE;
	BOOL SwitchImage = FALSE;
	SDL_Texture* pTexture;
	while (!quit) {
		SDL_PollEvent(pEvt);
		switch ((*pEvt).type)
		{
		case SDL_QUIT:
			quit = TRUE;
			break;

		case SDL_MOUSEBUTTONDOWN:
			if((*pEvt).button.button==SDL_BUTTON_LEFT)
			{
				if (SwitchImage == TRUE) {
					SwitchImage = FALSE;
					if(!(*listTexture).empty())
					{
						PlayMusic(TEXT("play Resources\\ÌøÔ¾_update.mp3"));
						pTexture = (*listTexture).front(); (*listTexture).pop();
						SDL_RenderClear(pRender);
						SDL_RenderCopy(pRender, pTexture, NULL, NULL);
						SDL_RenderPresent(pRender);
					}
				}
			}
			break;

		default:
			SwitchImage = TRUE;

		}
	}
}

int PlayMusic(const wchar_t* Cmd)
{
	
	return mciSendString(Cmd, NULL, 0, NULL);
}