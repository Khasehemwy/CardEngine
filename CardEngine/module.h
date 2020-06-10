#pragma once



class Image;
class Text;
class SystemModule;
class UserModule;
class GameModule;

//map<string, void*>Resources;

//ͼ��ģ�飬��ȾͼƬ
class Image
{
private:
	const SDL_Surface* imageSurface;
	const SDL_Texture* imageTexture;
public:	
	string imageName;				//ͼƬ�ļ�����
	SDL_Rect imageRect;				//ͼƬλ�úʹ�С
	unsigned int imageAlpha;		//ͼƬ͸����

	const SDL_Texture* GetTexture();
	const SDL_Surface* GetSurface();
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
	unsigned int value;				//FPS��ֵ
};


//ϵͳģ�飬�û�������и���
class SystemModule
{
private:
	HINSTANCE hInstance;			//Ӧ��ʵ�����
	SDL_Window* pWindow;			//����ָ��
	SDL_Renderer* pRenderer;		//��Ⱦָ��
	TTF_Font* pDefaultFont;			//Ĭ������ָ��
	SDL_Event event;

public:
	SystemModule();

	int SetWindow(SDL_Window*);
	int SetRenderer(SDL_Renderer*);
	int SetFont(TTF_Font*);
	SDL_Window* GetWindow();
	SDL_Renderer* GetRenderer();
	TTF_Font* GetDefaultFont();
	SDL_Event* GetEvent();
};


//�û�ģ�飬���ݲ�ͬ�趨���и���
class UserModule
{
public:
	string title;					//���ڱ���
	SIZE windowSize;				//���ڴ�С
	FPS FPS;						//FPS֡��
	BOOL showFPS;					//�Ƿ���ʾFPS

	UserModule() :
		title((string)"Game"+(string)CardEngine)
	{}
};


class GameModule :public UserModule
{
public:
	SystemModule system;
	//UserModule user;
};