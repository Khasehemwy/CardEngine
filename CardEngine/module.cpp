#pragma once

#include"includes.h"


extern map<const char*, ResourcesModule*>Resources;
extern map<const char*, RenderObject*>renderedTexture;

//=======系统模块=======*/

SystemModule::SystemModule() :
	pWindow(), pRenderer(), pDefaultFont(),
	hInstance(), event()
{}

//设置窗口
int SystemModule::SetWindow(SDL_Window* pWin)
{
	this->pWindow = pWin;
	if (this->pWindow == NULL) { return -1; }
	return 0;
}

//设置渲染
int SystemModule::SetRenderer(SDL_Renderer* pRenderer)
{
	this->pRenderer = pRenderer;
	if (this->pRenderer == NULL) { return -1; }
	return 0;
}


//设置字体
int SystemModule::SetFont(TTF_Font* pFont)
{
	this->pDefaultFont = pFont;
	if (this->pDefaultFont == NULL) { return -1; }
	return 0;
}

//获取系统组件
SDL_Event* SystemModule::GetEvent()
{
	return &(this->event);
}
SDL_Window* SystemModule::GetWindow()
{
	return this->pWindow;
}
SDL_Renderer* SystemModule::GetRenderer()
{
	return this->pRenderer;
}

TTF_Font* SystemModule::GetDefaultFont()
{
	return this->pDefaultFont;
}
//===================================================================End*/



//=======游戏引擎模块,统一管理system和user模块=======*/
EngineModule::EngineModule()
{}


//用户模块
UserModule::UserModule():
	title("Game"  _Card_CardEngine)
{

}

//FPS模块，默认60
FPS::FPS() :
	value(60), 
	interval(0.016)
{}
//===================================================================End*/



//=======游戏组件模块=======*/
GameObject::GameObject():
	scale(1),
	datumPoint(_Card_DatumPoint_UpperLeft),
	rect({ 0,0,0,0 })
{
}

GameObject::GameObject(const char* name):
	scale(1),
	datumPoint(_Card_DatumPoint_UpperLeft),
	rect({ 0,0,0,0 })
{
	this->name = name;
	Card_LoadGameObject(name);
}


//-------处理函数-------*/
void GameObject::Present()
{
	GameObject game = Card_PresentGameObject(this->name);
	this->rect = game.rect;
}
void GameObject::AddImage(Image& image)
{
	Card_GameObjectAddImage(this->name, image.name);
}



//-------设置属性-------*/
// SetSize
void GameObject::SetSize(int w, int h)
{
	this->rect.w = w;
	this->rect.h = h;
	Card_SetSizeObject(this->name, w, h);
}
void GameObject::SetSize(double scale)
{
	this->scale = scale;
	Card_SetSizeObject(this->name, scale);
}

//SetPosition
void GameObject::SetPosition(int x, int y)
{
	this->rect.x = x;
	this->rect.y = y;
	Card_SetPositionObject(this->name, x, y);
}

//SetDatumPoint
void GameObject::SetDatumPoint(int datumPointChoice)
{
	this->datumPoint = datumPoint;
	Card_SetDatumPointObject(this->name, datumPointChoice);
}

//-------图片子类-------*/
//SetImageAlpha
void GameObject::SetImageAlpha(int alpha)
{
	Card_SetAlphaImage(this->name, alpha);
}

//SetAnimationSpeed
void GameObject::SetAnimationSpeed(double speed)
{
	Card_SetSpeedAnimation(this->name, speed);
}

//ChooseAnimation
void GameObject::ChooseAnimation(Image& animation, SDL_RendererFlip rendererFlip)
{
	Card_ChooseAnimation(this->name, animation.name, rendererFlip);
}

//SetAnimationLoop
void GameObject::SetAnimationLoop(Image& animation, BOOL loop)
{
	Card_SetLoopAnimation(this->name, animation.name, loop);
}

//SetAnimationReplay
void GameObject::SetAnimationReplay(Image& animation)
{
	Card_SetReplayAnimation(this->name, animation.name);
}


//-------获取状态-------*/
// GetAnimationEndState
BOOL GameObject::GetAnimationEndState(Image& animation)
{
	return Card_GetAnimationEndState(this->name, animation.name);
}
//===================================================================End*/




//=======图片模块=======*/
Image::Image() :
	imageAlpha(255),
	animationSpeed(1.0),
	animationLoop(TRUE)
{}

Image::Image(const char* name) : 
	imageAlpha(255),
	animationSpeed(1.0),
	animationLoop(TRUE)
{
	this->name = name;
}


void Image::Load(const char* filePath)
{
	Card_LoadImage(filePath, this->name);
}


void Image::SetAlpha(int alpha)
{
	Card_SetAlphaImage(this->gameObjectName, alpha);
}

void Image::SetAnimationSpeed(double speed)
{
	Card_SetSpeedAnimation(this->gameObjectName, speed);
}
//===================================================================End*/



//=======文字模块=======*/
// TODO
Text::Text()
{}
//===================================================================End*/






//=======渲染模块=======*/
RenderObject::RenderObject() :
	indexTexture(0),
	animationName("default")
{}
//===================================================================End*/
