#pragma once

/*-------使用引擎-------*/

//使用引擎
void Card_Start(GameModule* );
void Card_Update(GameModule* );
void Card_UpdateSystem(GameModule* );

int Card_Delay();
int Card_Repeat();

SDL_Event* Card_GetEvent();

//系统自动处理
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);


/*-------处理系统模块-------*/
GameModule* Card_Initial(HINSTANCE hInstance);

void Card_HandleError();

void Card_HandleEvent(GameModule* pGame);

void Card_Run(GameModule* pGame);

void Card_SetTitle(GameModule* pGame, const char* pTitle);

void Card_SetWindowSize(GameModule* pGame, SIZE* size);



/*-------处理图片-------*/
Image* Card_LoadImage(const char* filePath, const char* fileName);

void Card_SetAlphaImage(const char* fileName, int alpha);
void Card_SetSpeedAnimation(const char* fileName, double speed);
void Card_ChooseAnimation(const char* fileName, const char* animationName, SDL_RendererFlip rendererFlip);



/*-------处理游戏组件-------*/
void Card_LoadGameObject(const char* name);
void Card_PresentGameObject(const char* fileName);
void Card_GameObjectAddImage(const char* gameObjectName, const char* imageName);



/*-------处理渲染-------*/
void Card_RenderPresent(GameModule* pGame, const std::chrono::steady_clock::time_point& nowTimePoint);

//设置物体属性
void Card_SetPositionObject(const char* fileName, int x, int y);

void Card_SetSizeObject(const char* fileName, int w, int h);
void Card_SetSizeObject(const char* fileName, double scale);

void Card_SetDatumPointObject(const char* fileName, int datumPointChoice);



