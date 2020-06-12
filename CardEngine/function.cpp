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
		game.title,
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
		"system\\defaultFont.ttf", _DefaultFontSize
	));
	if (ret < 0) { Card_HandleError(); }


	return &game;
}

void Card_HandleEvent(GameModule* pGame)
{
	//mutex tmpMutex;
	BOOL quit = FALSE;
	SDL_Event* pEvent = pGame->system.GetEvent();
	while (!quit)
	{
		Card_RenderPresent(pGame);
		SDL_WaitEvent(pEvent);
		//SDL_Log("%d", *pEvent);
		switch (pEvent->type)
		{
		case SDL_QUIT:
			quit = TRUE;
			break;

		case SDL_KEYDOWN:
			switch (pEvent->key.keysym.sym) {
			case SDLK_F4:
			case SDL_SCANCODE_F4:
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
				break;
			}
		}
	}
	SDL_Log("sss");
}

void Card_Run(GameModule* pGame)
{
	/*pGame->system.SetRendererForRun(SDL_CreateRenderer(
	//	pGame->system.GetWindow(),
	//	-1,
	//	SDL_RENDERER_ACCELERATED
	//));*/
	Card_HandleEvent(pGame);
}
//thread threadSystem(Card_Run);

void Card_HandleError(){}


/*-------图片-------*/
void Card_LoadImage(const char* filePath, const char* fileName)
{
	SDL_Surface* pSurface = IMG_Load(filePath);
	static Image image(pSurface);
	
	image.imageName = fileName;
	image.imageRect.w = pSurface->w;
	image.imageRect.h = pSurface->h;
	image.imageRect.x = image.imageRect.y = 0;

	//存储资源信息
	static ResourcesModule resourcesThis;
	resourcesThis.object = &image;
	resourcesThis.kind = _Image;
	Resources[fileName] = &resourcesThis;

}


//将图片加入渲染区
void Card_PresentImage(GameModule* pGame,const char* fileName)
{
	//mutex tmpMutex;
	//tmpMutex.lock();
	Image* image = (Image*)Resources[fileName]->object;
	static RenderObject renderThis;

	renderThis.pRect = &(image->imageRect);
	renderThis.pSurface = image->GetSurface();
	//renderThis.pTexture = SDL_CreateTextureFromSurface(pGame->system.GetRenderer(), image->GetSurface());
	SDL_SetTextureAlphaMod(renderThis.pTexture, image->imageAlpha);

	renderedTexture[fileName] = &renderThis;
	//tmpMutex.unlock();
}


/*-------渲染-------*/
void Card_RenderPresent(GameModule* pGame)
{
	SDL_Renderer* pRender = pGame->system.GetRenderer();
	SDL_RenderClear(pRender);
	SDL_SetRenderDrawColor(pRender, 25, 64, 82, 255);
	for (auto renderedThis : renderedTexture) {
		if (renderedThis.second->pTexture == NULL) {
			renderedThis.second->pTexture = SDL_CreateTextureFromSurface(pGame->system.GetRenderer(), renderedThis.second->pSurface);
		}
		SDL_RenderSetViewport(pRender,renderedThis.second->pRect);
		SDL_RenderCopy(pRender, renderedThis.second->pTexture, NULL, NULL);
	}
	
	SDL_RenderPresent(pRender);
}


//设置物体属性
void Card_MoveObject(const char*fileName, int x, int y)
{
	const char* objectKind = Resources[fileName]->kind;
	if (objectKind == _Image) {
		renderedTexture[fileName]->pRect->x = x;
		renderedTexture[fileName]->pRect->y = y;
	}
}

void Card_SetSizeObject(const char* fileName, int w, int h)
{
	const char* objectKind = Resources[fileName]->kind;
	if (objectKind == _Image) {
		renderedTexture[fileName]->pRect->w = w;
		renderedTexture[fileName]->pRect->h = h;
	}
}




/*-------User Module用户模块-------*/
void Card_SetTitle(GameModule* pGame, const char* pTitle)
{
	SDL_SetWindowTitle(pGame->system.GetWindow(), ((string)pTitle+_CardEngine).c_str());
	pGame->title = ((string)pTitle+_CardEngine).c_str();
}

void Card_SetWindowSize(GameModule* pGame, SIZE* size)
{
	SDL_SetWindowSize(pGame->system.GetWindow(), size->cx, size->cy);
	pGame->windowSize = *size;
}