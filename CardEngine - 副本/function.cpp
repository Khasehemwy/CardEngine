#pragma once

#include"includes.h"


static map<const char*, ResourcesModule*>Resources;
static map<const char*, RenderObject*>renderedTexture;

static SDL_Event Card_GetEvent_Event;

/*-------引擎系统-------*/

//系统自动处理
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//初始化引擎
	GameModule* pGame = Card_Initial(hInstance);
	
	Card_Start(pGame);
	//创建多线程
	thread userThread(Card_UpdateSystem, pGame);
	userThread.detach();


	//处理事件
	Card_Run(pGame);

	return 0;
}


//重复执行的更新函数
void Card_UpdateSystem(GameModule* pGame)
{
	auto beforeTimePoint = std::chrono::steady_clock::now();
	auto nowTimePoint = beforeTimePoint;
	std::chrono::duration<double> timeInterval;

	while (1) {
		nowTimePoint = std::chrono::steady_clock::now();
		timeInterval = nowTimePoint - beforeTimePoint;

		//限制帧率
		if (timeInterval >= pGame->FPS.interval) {
			beforeTimePoint = nowTimePoint;

			Card_Update(pGame);
		}
	}
}

//计时器
int Card_Delay()
{
	return 0;
}
int Card_Repeat()
{
	return 0;
}


//事件返回
SDL_Event* Card_GetEvent()
{
	return &Card_GetEvent_Event;
}




/*-------初始化-------*/
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

	//初始化渲染(Renderer)
	ret = game.system.SetRenderer(SDL_CreateRenderer(
		game.system.GetWindow(),
		-1,
		SDL_RENDERER_ACCELERATED
	));
	if (ret < 0) { Card_HandleError(); }

	//初始化字体
	TTF_Init();
	ret = game.system.SetFont(TTF_OpenFont(
		"system\\defaultFont.ttf", _Card_DefaultFontSize
	));
	if (ret < 0) { Card_HandleError(); }


	return &game;
}


/*-------事件处理-------*/
void Card_HandleEvent(GameModule* pGame)
{
	auto beforeTimePoint = std::chrono::steady_clock::now();
	auto nowTimePoint = beforeTimePoint;
	std::chrono::duration<double> timeInterval;

	BOOL quit = FALSE;
	SDL_Event* pEvent = pGame->system.GetEvent();

	while (!quit)
	{
		nowTimePoint = std::chrono::steady_clock::now();
		timeInterval = nowTimePoint - beforeTimePoint;

		if (timeInterval >= pGame->FPS.interval) {
			beforeTimePoint = nowTimePoint;

			SDL_PollEvent(pEvent);
			Card_RenderPresent(pGame,nowTimePoint);
			Card_GetEvent_Event = *pEvent;
			//SDL_Log("%d", Card_GetEvent_Event);
			switch (pEvent->type)
			{
			case SDL_QUIT:
				quit = TRUE;
				break;

			case SDL_KEYDOWN:
				switch (pEvent->key.keysym.sym) {
				case SDLK_ESCAPE:case SDL_SCANCODE_ESCAPE:
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
						if (pEvent->key.keysym.sym == SDLK_F4 || pEvent->key.keysym.sym == SDL_SCANCODE_F4) {
							SDL_SetWindowBordered(pGame->system.GetWindow(), SDL_FALSE);
							SDL_Rect rectWindow;
							SDL_GetDisplayBounds(0, &rectWindow);
							SDL_SetWindowSize(pGame->system.GetWindow(), rectWindow.w, rectWindow.h);
							SDL_SetWindowPosition(pGame->system.GetWindow(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
						}
					}
					break;
				}
			}
		}
	}
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

void Card_HandleError(){}


/*-------渲染-------*/
void Card_RenderPresent(GameModule* pGame, const std::chrono::steady_clock::time_point& nowTimePoint)
{
	SDL_Renderer* pRender = pGame->system.GetRenderer();
	
	SDL_RenderClear(pRender);
	SDL_SetRenderDrawColor(pRender, 25, 64, 82, 255);

	
	for (auto& renderedThis : renderedTexture) {

		//创建纹理
		if (renderedThis.second->renderInfo[renderedThis.second->animationName].vectorTexture.size() == 0) {
			SDL_Texture* pTexture;
			for (auto& usedSurface : *(renderedThis.second->renderInfo[renderedThis.second->animationName].vectorSurface)) {
				pTexture = SDL_CreateTextureFromSurface(pRender, usedSurface);
				renderedThis.second->renderInfo[renderedThis.second->animationName].vectorTexture.push_back(pTexture);
			}
		}
		
		/*动画*/
		if (nowTimePoint - renderedThis.second->beforeTimePoint >= renderedThis.second->intervalTime) {
			renderedThis.second->indexTexture++;
			renderedThis.second->beforeTimePoint = nowTimePoint;
			if (renderedThis.second->indexTexture >= renderedThis.second->renderInfo[renderedThis.second->animationName].vectorTexture.size()) {
				renderedThis.second->indexTexture = 0;
			}
		}

		//大小
		SDL_Rect tmpRect;
		tmpRect.w = (*renderedThis.second->renderInfo[renderedThis.second->animationName].vectorSurface)
						[renderedThis.second->indexTexture]->w * renderedThis.second->scale;
		tmpRect.h = (*renderedThis.second->renderInfo[renderedThis.second->animationName].vectorSurface)
						[renderedThis.second->indexTexture]->h * renderedThis.second->scale;

		//坐标基准点
		switch (renderedThis.second->datumPoint)
		{
		case _Card_UpperLeft:
			tmpRect.x = renderedThis.second->rect.x;
			tmpRect.y = renderedThis.second->rect.y;
			break;

		case _Card_BottomLeft:
			tmpRect.x = renderedThis.second->rect.x;
			tmpRect.y = renderedThis.second->rect.y-
						(double)((*renderedThis.second->renderInfo[renderedThis.second->animationName].vectorSurface)
							[renderedThis.second->indexTexture]->h-renderedThis.second->rect.h)
							*renderedThis.second->scale;

		}

		SDL_SetTextureAlphaMod(renderedThis.second->renderInfo[renderedThis.second->animationName].vectorTexture[renderedThis.second->indexTexture]
								, renderedThis.second->alpha);

		SDL_RenderCopy(pRender, renderedThis.second->renderInfo[renderedThis.second->animationName].vectorTexture[renderedThis.second->indexTexture]
						, NULL, &tmpRect);

	}
	
	SDL_RenderPresent(pRender);
}


/*-------图片-------*/

Image* Card_LoadImage(const char* filePath, const char* fileName)
{
	SDL_Surface* pSurface = IMG_Load(filePath);
	
	if (!Resources[fileName]) {
		Image* image = new Image();

		image->vectorSurface.push_back(pSurface);
		image->name = fileName;
		image->rect.w = pSurface->w;
		image->rect.h = pSurface->h;
		image->rect.x = image->rect.y = 0;

		//载入资源
		ResourcesModule* resourcesThis = new ResourcesModule();
		resourcesThis->object = image;
		resourcesThis->kind = _Card_GameObject;
		Resources[fileName] = resourcesThis;
	}
	else {
		Image* image = (Image*)(Resources[fileName]->object);
		image->vectorSurface.push_back(pSurface);
	}

	return (Image*)(Resources[fileName]->object);
}


//渲染图片

//void Card_PresentGameObject(Image* image)//暂停使用
//{
//	RenderObject* renderThis=new RenderObject();
//
//	renderThis->rect = (image->rect);
//	renderThis->vectorSurface = &image->vectorSurface;
//	renderThis->intervalTime = (std::chrono::duration<double>)((1 / image->animationSpeed) / image->vectorSurface.size());
//
//	renderedTexture[image->name] = renderThis;
//}/*-----------------------------------暂停使用*/

void Card_PresentGameObject(const char* fileName)
{
	Image* image = (Image*)Resources[fileName]->object;
	RenderObject* renderThis=new RenderObject();

	renderThis->rect = image->rect;
	renderThis->scale = image->scale;
	renderThis->datumPoint = image->datumPoint;
	renderThis->renderInfo[image->name].vectorSurface = &image->vectorSurface;
	renderThis->animationName = image->name;
	renderThis->intervalTime = (std::chrono::duration<double>)((1 / image->animationSpeed) / image->vectorSurface.size());

	renderedTexture[image->name] = renderThis;
}




/*-------设置物体属性-------*/
void Card_SetPositionObject(const char*fileName, int x, int y)
{
	int objectKind = Resources[fileName]->kind;
	if (objectKind == _Card_GameObject) {
		renderedTexture[fileName]->rect.x = x;
		renderedTexture[fileName]->rect.y = y;
	}
}

void Card_SetSizeObject(const char* fileName, int w, int h)
{
	int objectKind = Resources[fileName]->kind;
	if (objectKind == _Card_GameObject) {
		renderedTexture[fileName]->rect.w = w;
		renderedTexture[fileName]->rect.h = h;
	}
}
void Card_SetSizeObject(const char* fileName, double scale)
{
	int objectKind = Resources[fileName]->kind;
	if (objectKind == _Card_GameObject) {
		renderedTexture[fileName]->scale = scale;
	}
}
void Card_SetDatumPointObject(const char* fileName,int datumPointChoice)
{
	int objectKind = Resources[fileName]->kind;
	if (objectKind == _Card_GameObject) {
		renderedTexture[fileName]->datumPoint = datumPointChoice;
	}
}


void Card_SetAlphaImage(const char* fileName, int alpha)
{
	int objectKind = Resources[fileName]->kind;
	if (objectKind == _Card_GameObject) {
		renderedTexture[fileName]->alpha = alpha;
	}
}

void Card_SetSpeedAnimation(const char* fileName, double speed)
{
	int objectKind = Resources[fileName]->kind;
	if (objectKind == _Card_GameObject) {
		for (auto& animation : renderedTexture[fileName]->renderInfo) { //更改该物体所有动画的速度
			renderedTexture[fileName]->intervalTime = (std::chrono::duration<double>)((1 / speed) / animation.second.vectorSurface->size());
		}
	}
}




/*-------User Module用户模块-------*/
void Card_SetTitle(GameModule* pGame, const char* pTitle)
{
	SDL_SetWindowTitle(pGame->system.GetWindow(), ((string)pTitle+_Card_CardEngine).c_str());
	pGame->title = ((string)pTitle+_Card_CardEngine).c_str();
}

void Card_SetWindowSize(GameModule* pGame, SIZE* size)
{
	SDL_SetWindowSize(pGame->system.GetWindow(), size->cx, size->cy);
	pGame->windowSize = *size;
}