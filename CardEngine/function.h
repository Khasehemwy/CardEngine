#pragma once

//=======使用引擎=======*/

//使用引擎
void Card_Start(EngineModule* pGame);
void Card_Update(EngineModule* pGame);
void Card_UpdateSystem(EngineModule* pGame);

//TODO
int Card_Delay();
int Card_Repeat();

//获取事件
SDL_Event* Card_GetEvent();

//系统自动处理
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
//===================================================================End*/



//=======处理引擎模块=======*/
EngineModule* Card_Initial(HINSTANCE hInstance);

void Card_HandleError();//TODO

void Card_HandleEvent(EngineModule* pGame);

void Card_Run(EngineModule* pGame);

void Card_SetTitle(EngineModule* pGame, const char* pTitle);

void Card_SetWindowSize(EngineModule* pGame, SIZE* size);
//===================================================================End*/



//=======处理图片=======*/
Image* Card_LoadImage(const char* filePath, const char* fileName);

void Card_SetAlphaImage(const char* fileName, int alpha);
void Card_SetSpeedAnimation(const char* fileName, double speed);
void Card_ChooseAnimation(const char* fileName, const char* animationName, SDL_RendererFlip rendererFlip);
void Card_SetLoopAnimation(const char* fileName, const char* animationName, BOOL loop);
void Card_SetReplayAnimation(const char* fileName, const char* animationName);
//===================================================================End*/




//=======处理游戏组件=======*/
void Card_LoadGameObject(const char* name);

//该函数在主线程创建一个GameObject变量,并返回值,以便子线程可获取GameObject状态
GameObject Card_PresentGameObject(const char* fileName);

void Card_GameObjectAddImage(const char* gameObjectName, const char* imageName);

BOOL Card_GetAnimationEndState(const char* fileName, const char* animationName);
//===================================================================End*/



//=======处理渲染=======*/

//nowTimePoint用于处理帧率
void Card_RenderPresent(EngineModule* pGame, const std::chrono::steady_clock::time_point& nowTimePoint);

//设置物体属性
void Card_SetPositionObject(const char* fileName, int x, int y);

void Card_SetSizeObject(const char* fileName, int w, int h);
void Card_SetSizeObject(const char* fileName, double scale);

void Card_SetDatumPointObject(const char* fileName, int datumPointChoice);
//===================================================================End*/
