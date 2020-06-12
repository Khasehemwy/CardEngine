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

//ͼ��ģ�飬��ȾͼƬ
class Image
{
private:
	SDL_Surface* imageSurface;
public:	
	string imageName;				//ͼƬ�ļ�����
	SDL_Rect imageRect;				//ͼƬλ�úʹ�С
	unsigned int imageAlpha;		//ͼƬ͸����

	Image(SDL_Surface*);

	SDL_Surface* GetSurface();
};


//�ı�ģ�飬��Ⱦ����
class Text :public Image
{
public:
	const char* fontName;			//�����ļ�����
	SDL_Rect fontRect;				//����λ�úʹ�С
	unsigned int fontAlpha;			//����͸����
};


//FPSģ��
class FPS :public Text
{
public:
	unsigned int value;				//FPS��ֵ
};


//ϵͳģ�飬�û�������и���
class SystemModule
{
private:
	HINSTANCE hInstance;			//Ӧ��ʵ�����
	SDL_Window* pWindow;			//����ָ��
	SDL_Renderer* pRenderer;		//��Ⱦָ��
	SDL_Renderer* pRendererForRun;
	TTF_Font* pDefaultFont;			//Ĭ������ָ��
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


//�û�ģ�飬���ݲ�ͬ�趨���и���
class UserModule
{
public:
	const char* title;				//���ڱ���
	SIZE windowSize;				//���ڴ�С
	//FPS FPS;						//FPS֡��
	//BOOL showFPS;					//�Ƿ���ʾFPS

	UserModule();
};


class GameModule :public UserModule
{
public:
	SystemModule system;
	//UserModule user;
};