#pragma once

#include"includes.h"

//储存资源*/
static map<const char*, ResourcesModule*>Resources;
//储存即将渲染的物体*/
static map<const char*, RenderObject*>renderedTexture;

//返回给子线程的事件*/
static SDL_Event Card_GetEvent_Event;


//=======引擎系统=======*/

//系统自动处理
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//初始化引擎
	EngineModule* pGame = Card_Initial(hInstance);
	
	Card_Start(pGame);
	//创建多线程
	thread userThread(Card_UpdateSystem, pGame);
	userThread.detach();


	//处理事件
	Card_Run(pGame);

	return 0;
}


//Update函数,重复执行
void Card_UpdateSystem(EngineModule* pGame)
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
//TODO
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

//===================================================================End*/




//=======初始化=======*/
EngineModule* Card_Initial(HINSTANCE hInstance)
{
	static EngineModule game;

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
		NULL
		//SDL_WINDOW_RESIZABLE
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
//===================================================================End*/



//=======事件处理=======*/
void Card_HandleEvent(EngineModule* pGame)
{
	//用于设置帧率
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

			switch (pEvent->type)
			{
			case SDL_QUIT:
				quit = TRUE;
				break;

			case SDL_KEYDOWN:
				switch (pEvent->key.keysym.sym) {
				case SDLK_ESCAPE:case SDL_SCANCODE_ESCAPE:
				case SDLK_F4:case SDL_SCANCODE_F4:
					//窗口时按下F4,全屏;全屏时按下esc或F4,退出全屏*/
					if (SDL_GetWindowFlags(pGame->system.GetWindow()) & SDL_WINDOW_FULLSCREEN ||
						SDL_GetWindowFlags(pGame->system.GetWindow()) & SDL_WINDOW_FULLSCREEN_DESKTOP ||
						SDL_GetWindowFlags(pGame->system.GetWindow()) & SDL_WINDOW_BORDERLESS)
					{
						SDL_SetWindowBordered(pGame->system.GetWindow(), SDL_TRUE);
						//SDL_SetWindowResizable(pGame->system.GetWindow(), SDL_TRUE);
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


//=======运行引擎=======*/
void Card_Run(EngineModule* pGame)
{
	Card_HandleEvent(pGame);
}
//===================================================================End*/



//=======错误处理=======*/
//TODO
void Card_HandleError(){}
//===================================================================End*/



//=======渲染=======*/
void Card_RenderPresent(EngineModule* pGame, const std::chrono::steady_clock::time_point& nowTimePoint)
{
	SDL_Renderer* pRender = pGame->system.GetRenderer();
	
	SDL_RenderClear(pRender);
	SDL_SetRenderDrawColor(pRender, 25, 64, 82, 255);//经典蓝

	
	for (auto& renderedThis : renderedTexture) {

		//创建纹理
		if (renderedThis.second->animationInfo[renderedThis.second->animationName].vectorTexture.size() == 0) {
			SDL_Texture* pTexture;
			for (auto& usedSurface : *(renderedThis.second->animationInfo[renderedThis.second->animationName].vectorSurface)) {
				pTexture = SDL_CreateTextureFromSurface(pRender, usedSurface);
				renderedThis.second->animationInfo[renderedThis.second->animationName].vectorTexture.push_back(pTexture);
			}
		}
		
		//动画*/

		//跳过到达末尾的非循环动画
		if (renderedThis.second->animationInfo[renderedThis.second->animationName].animationLoop == FALSE
			&& renderedThis.second->animationInfo[renderedThis.second->animationName].animationEnd == TRUE) {
			;
		}

		else {
			if (nowTimePoint - renderedThis.second->beforeTimePoint >= renderedThis.second->intervalTime) {
				renderedThis.second->indexTexture++;
				renderedThis.second->beforeTimePoint = nowTimePoint;
			}

			//判断动画是否到达结尾
			if (renderedThis.second->indexTexture >= renderedThis.second->animationInfo[renderedThis.second->animationName].vectorTexture.size()-1
				|| renderedThis.second->indexTexture >= (*renderedThis.second->animationInfo[renderedThis.second->animationName].vectorSurface).size()-1) {
				renderedThis.second->animationInfo[renderedThis.second->animationName].animationEnd = TRUE;
			}
			else {
				renderedThis.second->animationInfo[renderedThis.second->animationName].animationEnd = FALSE;
			}
		}
		//防止数组越界
		if (renderedThis.second->indexTexture >= renderedThis.second->animationInfo[renderedThis.second->animationName].vectorTexture.size()
			|| renderedThis.second->indexTexture >= (*renderedThis.second->animationInfo[renderedThis.second->animationName].vectorSurface).size()) {
			renderedThis.second->indexTexture = 0;
		}




		//放置方式*/
		SDL_Rect tmpRect;
		SDL_Rect* pTmpRect = &tmpRect;

		if (renderedThis.second->scale == _Card_Size_FullWindow) { //全屏幕
			SDL_GetWindowSize(pGame->system.GetWindow(), &tmpRect.w, &tmpRect.h);
			tmpRect.x = tmpRect.y = 0;
			//pTmpRect = NULL;
		}
		else {
			//大小
			tmpRect.w = (*renderedThis.second->animationInfo[renderedThis.second->animationName].vectorSurface)
							[renderedThis.second->indexTexture]->w * renderedThis.second->scale;
			tmpRect.h = (*renderedThis.second->animationInfo[renderedThis.second->animationName].vectorSurface)
							[renderedThis.second->indexTexture]->h * renderedThis.second->scale;

			//坐标基准点
			switch (renderedThis.second->datumPoint)
			{
			case _Card_DatumPoint_UpperLeft:
				tmpRect.x = renderedThis.second->rect.x;
				tmpRect.y = renderedThis.second->rect.y;
				break;


			case _Card_DatumPoint_BottomLeft:
				tmpRect.x = renderedThis.second->rect.x;
				tmpRect.y = renderedThis.second->rect.y -
					(double)((*renderedThis.second->animationInfo[renderedThis.second->animationName].vectorSurface)
						[renderedThis.second->indexTexture]->h - renderedThis.second->rect.h)
					* renderedThis.second->scale;
				break;


			case _Card_DatumPoint_Center:
				tmpRect.x = renderedThis.second->rect.x -
					(double)((*renderedThis.second->animationInfo[renderedThis.second->animationName].vectorSurface)
						[renderedThis.second->indexTexture]->w - renderedThis.second->rect.w)/2
					* renderedThis.second->scale;
				tmpRect.y = renderedThis.second->rect.y -
					(double)((*renderedThis.second->animationInfo[renderedThis.second->animationName].vectorSurface)
						[renderedThis.second->indexTexture]->h - renderedThis.second->rect.h)/2
					* renderedThis.second->scale;
				break;
			}
		}




		SDL_SetTextureAlphaMod(renderedThis.second->animationInfo[renderedThis.second->animationName].vectorTexture[renderedThis.second->indexTexture]
			, renderedThis.second->alpha);
		
		SDL_RenderCopyEx(pRender, 
			renderedThis.second->animationInfo[renderedThis.second->animationName].vectorTexture[renderedThis.second->indexTexture], 
			NULL, 
			pTmpRect, 
			NULL, NULL, 
			renderedThis.second->imageFlip);

	}
	
	SDL_RenderPresent(pRender);
}
//===================================================================End*/



//=======图片=======*/

Image* Card_LoadImage(const char* filePath, const char* fileName)
{
	SDL_Surface* pSurface = IMG_Load(filePath);
	
	if (!Resources[fileName]) {
		Image* image = new Image();

		image->vectorSurface.push_back(pSurface);
		image->name = fileName;

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


//设置图片属性
void Card_SetAlphaImage(const char* fileName, int alpha)
{
	if (Resources[fileName] && renderedTexture[fileName]) {
		int objectKind = Resources[fileName]->kind;
		if (objectKind == _Card_GameObject) {
			renderedTexture[fileName]->alpha = alpha;
		}
	}
}

void Card_SetSpeedAnimation(const char* fileName, double speed)
{
	if (Resources[fileName] && renderedTexture[fileName]) {
		int objectKind = Resources[fileName]->kind;
		if (objectKind == _Card_GameObject) {
			for (auto& animation : renderedTexture[fileName]->animationInfo) { //更改该物体所有动画的速度
				renderedTexture[fileName]->intervalTime = (std::chrono::duration<double>)((1 / speed) / animation.second.vectorSurface->size());
			}
		}
	}
}
void Card_ChooseAnimation(const char* fileName, const char* animationName, SDL_RendererFlip rendererFlip)
{
	if (Resources[fileName] && renderedTexture[fileName]) {
		int objectKind = Resources[fileName]->kind;
		if (objectKind == _Card_GameObject) {
			renderedTexture[fileName]->animationName = animationName;
			renderedTexture[fileName]->imageFlip = rendererFlip;
		}
	}
}

void Card_SetLoopAnimation(const char* fileName, const char* animationName, BOOL loop)
{
	if (Resources[fileName] && renderedTexture[fileName]) {
		int objectKind = Resources[fileName]->kind;
		if (objectKind == _Card_GameObject) {
			renderedTexture[fileName]->animationInfo[animationName].animationLoop = loop;
		}
	}
}

void Card_SetReplayAnimation(const char* fileName, const char* animationName)
{
	if (Resources[fileName] && renderedTexture[fileName]) {
		int objectKind = Resources[fileName]->kind;
		if (objectKind == _Card_GameObject) {
			renderedTexture[fileName]->indexTexture = 0;
			renderedTexture[fileName]->animationInfo[animationName].animationEnd = FALSE;
		}
	}
}
//===================================================================End*/




//=======游戏组件=======*/

//void Card_PresentGameObject(Image* image)//暂停使用 FIXME
//{
//	RenderObject* renderThis=new RenderObject();
//
//	renderThis->rect = (image->rect);
//	renderThis->vectorSurface = &image->vectorSurface;
//	renderThis->intervalTime = (std::chrono::duration<double>)((1 / image->animationSpeed) / image->vectorSurface.size());
//
//	renderedTexture[image->name] = renderThis;
//}//-----------------------------------暂停使用*/
void Card_LoadGameObject(const char* name)
{
	if (!Resources[name]) {
		GameObject* pGame = new GameObject();
		ResourcesModule* resourcesThis = new ResourcesModule();
		resourcesThis->object = pGame;
		resourcesThis->kind = _Card_GameObject;
		Resources[name] = resourcesThis;
	}
}

void Card_GameObjectAddImage(const char* gameObjectName, const char* imageName)
{
	GameObject* pGame = (GameObject*)Resources[gameObjectName]->object;
	Image* image = (Image*)Resources[imageName]->object;

	image->gameObjectName = gameObjectName;

	pGame->name = gameObjectName;
	pGame->images[image->name] = image;
}

GameObject Card_PresentGameObject(const char* fileName)
{
	GameObject* pGame = (GameObject*)Resources[fileName]->object;

	if (!renderedTexture[pGame->name]) { //需要:显示物体前已经完成动画添加

		//储存第一张图片的大小作为默认大小
		pGame->rect.w = (*(*pGame->images.begin()).second->vectorSurface.begin())->w;
		pGame->rect.h = (*(*pGame->images.begin()).second->vectorSurface.begin())->h;
		pGame->rect.x = pGame->rect.y = 0;

		RenderObject* renderThis=new RenderObject();

		renderThis->rect = pGame->rect;
		renderThis->scale = pGame->scale;
		renderThis->datumPoint = pGame->datumPoint;

		for (auto& image : pGame->images) {
			renderThis->animationInfo[image.second->name].vectorSurface = &image.second->vectorSurface;
			renderThis->animationInfo[image.second->name].animationLoop = image.second->animationLoop;
			renderThis->animationInfo[image.second->name].animationEnd = image.second->animationEnd;
			renderThis->animationName = image.second->name;
			renderThis->intervalTime = (std::chrono::duration<double>)((1 / image.second->animationSpeed) / image.second->vectorSurface.size());
		}
		renderedTexture[pGame->name] = renderThis;
	}
	else {// TODO
		auto& renderThis = renderedTexture[pGame->name];
	}

	return *pGame;
}


//设置游戏组件属性*/

//Card_SetPositionObject
void Card_SetPositionObject(const char*fileName, int x, int y)
{
	if (Resources[fileName] && renderedTexture[fileName]) {
		int objectKind = Resources[fileName]->kind;
		if (objectKind == _Card_GameObject) {
			renderedTexture[fileName]->rect.x = x;
			renderedTexture[fileName]->rect.y = y;
		}
	}
}

//Card_SetSizeObject
void Card_SetSizeObject(const char* fileName, int w, int h)
{
	if (Resources[fileName] && renderedTexture[fileName]) {
		int objectKind = Resources[fileName]->kind;
		if (objectKind == _Card_GameObject) {
			renderedTexture[fileName]->rect.w = w;
			renderedTexture[fileName]->rect.h = h;
		}
	}
}
void Card_SetSizeObject(const char* fileName, double scale)
{
	if (Resources[fileName] && renderedTexture[fileName]) {
		int objectKind = Resources[fileName]->kind;
		if (objectKind == _Card_GameObject) {
			renderedTexture[fileName]->scale = scale;
		}
	}
}

//Card_SetDatumPointObject
void Card_SetDatumPointObject(const char* fileName,int datumPointChoice)
{
	if (Resources[fileName] && renderedTexture[fileName]) {
		int objectKind = Resources[fileName]->kind;
		if (objectKind == _Card_GameObject) {
			renderedTexture[fileName]->datumPoint = datumPointChoice;
		}
	}
}

//获取状态*/

//Card_GetAnimationEndState
BOOL Card_GetAnimationEndState(const char* fileName, const char* animationName)
{
	if (Resources[fileName] && renderedTexture[fileName]) {
		int objectKind = Resources[fileName]->kind;
		if (objectKind == _Card_GameObject) {
			return renderedTexture[fileName]->animationInfo[animationName].animationEnd;
		}
	}
}
//===================================================================End*/






//=======UserModule用户模块=======*/
void Card_SetTitle(EngineModule* pGame, const char* pTitle)
{
	SDL_SetWindowTitle(pGame->system.GetWindow(), ((string)pTitle+_Card_CardEngine).c_str());
	pGame->title = ((string)pTitle+_Card_CardEngine).c_str();
}

void Card_SetWindowSize(EngineModule* pGame, SIZE* size)
{
	SDL_SetWindowSize(pGame->system.GetWindow(), size->cx, size->cy);
	pGame->windowSize = *size;
}