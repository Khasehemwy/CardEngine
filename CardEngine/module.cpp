#pragma once

#include"includes.h"


/*-------ϵͳģ��-------*/

SystemModule::SystemModule() :
	pWindow(), pRenderer(), pDefaultFont(),
	hInstance(), event()
{}

//��ʼ������
int SystemModule::SetWindow(SDL_Window* pWin)
{
	this->pWindow = pWin;
	if (this->pWindow == NULL) { return -1; }
	return 0;
}

//��ʼ����Ⱦ��
int SystemModule::SetRenderer(SDL_Renderer* pRenderer)
{
	this->pRenderer = pRenderer;
	if (this->pRenderer == NULL) { return -1; }
	return 0;
}
int SystemModule::SetRendererForRun(SDL_Renderer* pRenderer)
{
	this->pRendererForRun = pRenderer;
	if (this->pRendererForRun == NULL) { return -1; }
	return 0;
}

//��ʼ��Ĭ������
int SystemModule::SetFont(TTF_Font* pFont)
{
	this->pDefaultFont = pFont;
	if (this->pDefaultFont == NULL) { return -1; }
	return 0;
}

//��ȡϵͳ���Ա
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
SDL_Renderer* SystemModule::GetRendererForRun()
{
	return this->pRendererForRun;
}
TTF_Font* SystemModule::GetDefaultFont()
{
	return this->pDefaultFont;
}


/*-------�û�ģ��-------*/
UserModule::UserModule():
	title("Game"  _CardEngine)
{

}





/*-------ͼƬģ��-------*/
Image::Image(SDL_Surface* pSurface) :imageSurface(pSurface)
{
	this->imageAlpha = 255;
}



SDL_Surface* Image::GetSurface()
{
	return this->imageSurface;
}
