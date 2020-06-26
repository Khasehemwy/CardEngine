#pragma once

#include"includes.h"


extern map<const char*, ResourcesModule*>Resources;
extern map<const char*, RenderObject*>renderedTexture;

/*-------系统模块-------*/

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



/*/-------游戏模块，包含系统和用户模块-------*/
GameModule::GameModule()
{}


/*-------用户模块-------*/
UserModule::UserModule():
	title("Game"  _Card_CardEngine)
{

}

//FPS模块，默认60
FPS::FPS() :
	value(60), 
	interval(0.016)
{}



/*-------游戏组件模块-------*/
GameObject::GameObject():
	scale(1),
	datumPoint(_Card_UpperLeft)
{}

GameObject::GameObject(const char* name):
	name(name)
{}


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


void GameObject::SetPosition(int x, int y)
{
	this->rect.x = x;
	this->rect.y = y;
	Card_SetPositionObject(this->name, x, y);
}

void GameObject::SetDatumPoint(int datumPointChoice)
{
	this->datumPoint = datumPoint;
	Card_SetDatumPointObject(this->name, datumPointChoice);
}

void GameObject::Present()
{
	Card_PresentGameObject(this->name);
}





/*-------图片模块-------*/
Image::Image() :
	imageAlpha(255),
	animationSpeed(2.0)
{}

Image::Image(const char*name)
{
	this->name = name;
	//Card_InitialImage(this);
}


void Image::Load(const char* filePath)
{
	Card_LoadImage(filePath, this->name);
}


void Image::SetAlpha(int alpha)
{
	Card_SetAlphaImage(this->name, alpha);
}

void Image::SetAnimationSpeed(double speed)
{
	Card_SetSpeedAnimation(this->name, speed);
}

/*-------文字模块-------*/
Text::Text()
{}






/*-------渲染模块-------*/
RenderObject::RenderObject() :
	indexTexture(0),
	animationName("default")
{}





