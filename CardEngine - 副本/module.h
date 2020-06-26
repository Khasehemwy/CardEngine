#pragma once

class GameModule;
class SystemModule;
class UserModule;
class ResourcesModule;
class Text;
class FPS;
class RenderObject;
class GameObject;
class Image;



//用于存储资源
class ResourcesModule
{
public:
	void* object;
	int kind;
};

//用于存储渲染的物体
class RenderInfo
{
public:
	vector<SDL_Surface*>* vectorSurface;
	vector<SDL_Texture*> vectorTexture;
};

class RenderObject
{
public:
	map < const char*, RenderInfo > renderInfo;
	SDL_Rect rect;
	int datumPoint;
	double scale;

	int alpha;					//图片透明度
	const char* animationName;	//选择进行渲染的动画

	//动画
	std::chrono::steady_clock::time_point beforeTimePoint;
	unsigned int indexTexture;									//两个渲染间的间隔时间
	std::chrono::duration<double> intervalTime;

	RenderObject();
};


//游戏组件
class GameObject
{
public:
	const char* name;				//名字
	SDL_Rect rect;					//大小和位置
	double scale;					//缩放程度
	int datumPoint;					//坐标基准点

	GameObject();
	GameObject(const char* name);

	void SetSize(int w, int h);
	void SetSize(double scale);
	void SetPosition(int x, int y);
	void SetDatumPoint(int datumPointChoice);

	void Present();
};

//图片
class Image :public GameObject
{
public:
	vector<SDL_Surface*> vectorSurface;

	unsigned int imageAlpha;		//图片透明度
	double animationSpeed;

	Image();
	Image(const char* name);

	void Load(const char* filePath);

	void SetAlpha(int alpha);
	void SetAnimationSpeed(double speed);
};

//文字
class Text :public Image
{
public:
	const char* fontName;			//字体名称
	SDL_Rect fontRect;				//字体位置和大小
	unsigned int fontAlpha;			//字体透明度

	Text();
};


//FPS模块
class FPS :public Text
{
public:
	unsigned int value;				//FPS大小
	std::chrono::duration<double> interval;

	FPS();
};



//系统模块，使用引擎时不应接触
class SystemModule
{
private:
	HINSTANCE hInstance;			//窗口句柄
	SDL_Window* pWindow;			//窗口
	SDL_Renderer* pRenderer;		//渲染器
	TTF_Font* pDefaultFont;			//默认字体
	SDL_Event event;

public:
	SystemModule();

	int SetWindow(SDL_Window* pWin);
	int SetRenderer(SDL_Renderer* pRenderer);
	int SetFont(TTF_Font* pFont);
	SDL_Window* GetWindow();
	SDL_Renderer* GetRenderer();
	TTF_Font* GetDefaultFont();
	SDL_Event* GetEvent();
};


//用户组件，可随意设置
class UserModule
{
public:
	const char* title;				//窗口标题
	SIZE windowSize;				//窗口大小
	FPS FPS;						//FPS
	//BOOL showFPS;					//是否显示FPS

	UserModule();
};


class GameModule :public UserModule
{
public:
	SystemModule system;

	GameModule();
};
