#pragma once

#include"includes.h"


/*-------系统模块-------*/

SystemModule::SystemModule() :
	pWindow(), pRenderer(), pDefaultFont(),
	hInstance(), event()
{}

//初始化窗口
int SystemModule::SetWindow(SDL_Window* pWin)
{
	this->pWindow = pWin;
	if (this->pWindow == NULL) { return -1; }
	return 0;
}

//初始化渲染器
int SystemModule::SetRenderer(SDL_Renderer* pRenderer)
{
	this->pRenderer = pRenderer;
	if (this->pRenderer == NULL) { return -1; }
	return 0;
}

//初始化默认字体
int SystemModule::SetFont(TTF_Font* pFont)
{
	this->pDefaultFont = pFont;
	if (this->pDefaultFont == NULL) { return -1; }
	return 0;
}

//获取系统类成员
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


/*-------用户模块-------*/






/*-------图片模块-------*/
const SDL_Texture* Image::GetTexture()
{
	return this->imageTexture;
}
const SDL_Surface* Image::GetSurface()
{
	return this->imageSurface;
}
