#pragma once

#include"includes.h"

GameModule* Card_Initial(HINSTANCE hInstance)
{
	static GameModule game;

	//初始化SDL
	auto ret = SDL_Init(SDL_INIT_EVERYTHING);
	if (ret < 0) { Card_HandleError(); }

	//初始化窗口(Window)
	SDL_Rect rectWindow;
	SDL_GetDisplayBounds(0, &rectWindow);
	ret = game.system.SetWindow(SDL_CreateWindow(
		game.title.c_str(),
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		rectWindow.w*0.6, rectWindow.h*0.6, 
		SDL_WINDOW_RESIZABLE
		//SDL_WINDOW_BORDERLESS
	));
	game.windowSize = { (LONG)(rectWindow.w * 0.6),(LONG)(rectWindow.h * 0.6) };
	if (ret < 0) { Card_HandleError(); }

	//初始化渲染器(Renderer)
	ret = game.system.SetRenderer(SDL_CreateRenderer(
		game.system.GetWindow(),
		-1,
		SDL_RENDERER_ACCELERATED
	));
	if (ret < 0) { Card_HandleError(); }

	//初始化默认字体
	TTF_Init();
	ret = game.system.SetFont(TTF_OpenFont(
		"system\\defaultFont.ttf", DefaultFontSize
	));
	if (ret < 0) { Card_HandleError(); }


	return &game;
}

void Card_HandleEvent(GameModule* pGame)
{
	BOOL quit = FALSE;
	SDL_Event* pEvent = pGame->system.GetEvent();
	while (!quit)
	{
		SDL_WaitEvent(pEvent);
		//SDL_Log("%d", *pEvent);
		switch (pEvent->type)
		{
		case SDL_QUIT:
			quit = TRUE;
			break;

		case SDL_KEYDOWN:
			switch (pEvent->key.keysym.sym) {
			case SDLK_F4:case SDL_SCANCODE_F4:
				//F4---full screen---全屏
				if (SDL_GetWindowFlags(pGame->system.GetWindow()) & SDL_WINDOW_FULLSCREEN ||
					SDL_GetWindowFlags(pGame->system.GetWindow()) & SDL_WINDOW_FULLSCREEN_DESKTOP ||
					SDL_GetWindowFlags(pGame->system.GetWindow()) & SDL_WINDOW_BORDERLESS)
				{
					SDL_SetWindowBordered(pGame->system.GetWindow(), SDL_TRUE);
					SDL_SetWindowResizable(pGame->system.GetWindow(), SDL_TRUE);
					SDL_SetWindowSize(pGame->system.GetWindow(), pGame->windowSize.cx, pGame->windowSize.cy);
					SDL_SetWindowPosition(pGame->system.GetWindow(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
				}
				else {
					SDL_SetWindowBordered(pGame->system.GetWindow(), SDL_FALSE);
					SDL_Rect rectWindow;
					SDL_GetDisplayBounds(0, &rectWindow);
					SDL_SetWindowSize(pGame->system.GetWindow(), rectWindow.w, rectWindow.h);
					SDL_SetWindowPosition(pGame->system.GetWindow(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
				}
			}

		default:
			SDL_SetRenderDrawColor(pGame->system.GetRenderer(), 25, 64, 82, 255);
			SDL_RenderClear(pGame->system.GetRenderer());
			SDL_RenderPresent(pGame->system.GetRenderer());
		}
	}
}

//void Card_LoadImage(string* filePath, string* fileName)
//{
//	SDL_Surface* pSurface = IMG_Load(filePath->c_str());
//	SDL_Texture* pTexture=SDL_CreateTextureFromSurface()
//	static Image image;
//}


void Card_Run(GameModule* pGame)
{
	Card_HandleEvent(pGame);
}

void Card_HandleError(){}


//User Module
void Card_SetTitle(GameModule* pGame, string* pTitle)
{
	SDL_SetWindowTitle(pGame->system.GetWindow(), ((*pTitle) + CardEngine).c_str());
	pGame->title = ((*pTitle) + CardEngine);
}

void Card_SetWindowSize(GameModule* pGame, SIZE* size)
{
	SDL_SetWindowSize(pGame->system.GetWindow(), size->cx, size->cy);
	pGame->windowSize = *size;
}