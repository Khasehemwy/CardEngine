#pragma once


class Image;
class Text;
class SystemModule;
class UserModule;
class GameModule;
class RenderObject;
class ResourcesModule;

static map<const char*, ResourcesModule*>Resources;
static map<const char*, RenderObject*>renderedTexture;


class ResourcesModule
{
public:
	void* object;
	const char* kind;
};

class RenderObject
{
public:
	SDL_Surface* pSurface;
	SDL_Texture* pTexture;
	SDL_Rect* pRect;
};

//图像模块，渲染图片
class Image
{
private:
	SDL_Surface* imageSurface;
public:	
	string imageName;				//图片文件名称
	SDL_Rect imageRect;				//图片位置和大小
	unsigned int imageAlpha;		//图片透明度

	Image(SDL_Surface*);

	SDL_Surface* GetSurface();
};


//文本模块，渲染文字
class Text :public Image
{
public:
	const char* fontName;			//字体文件名称
	SDL_Rect fontRect;				//文字位置和大小
	unsigned int fontAlpha;			//文字透明度
};


//FPS模块
class FPS :public Text
{
public:
	unsigned int value;				//FPS数值
};


//系统模块，用户不会进行更改
class SystemModule
{
private:
	HINSTANCE hInstance;			//应用实例句柄
	SDL_Window* pWindow;			//窗口指针
	SDL_Renderer* pRenderer;		//渲染指针
	SDL_Renderer* pRendererForRun;
	TTF_Font* pDefaultFont;			//默认字体指针
	SDL_Event event;

public:
	SystemModule();

	int SetWindow(SDL_Window*);
	int SetRenderer(SDL_Renderer*);
	int SetRendererForRun(SDL_Renderer*);
	int SetFont(TTF_Font*);
	SDL_Window* GetWindow();
	SDL_Renderer* GetRendererForRun();
	SDL_Renderer* GetRenderer();
	TTF_Font* GetDefaultFont();
	SDL_Event* GetEvent();
};


//用户模块，根据不同设定进行更改
class UserModule
{
public:
	const char* title;				//窗口标题
	SIZE windowSize;				//窗口大小
	//FPS FPS;						//FPS帧率
	//BOOL showFPS;					//是否显示FPS

	UserModule();
};


class GameModule :public UserModule
{
public:
	SystemModule system;
	//UserModule user;
};