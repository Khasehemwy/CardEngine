#pragma once
//类前置声明*/
class EngineModule;
class SystemModule;
class UserModule;
class ResourcesModule;
class Text;
class FPS;
class RenderObject;
class GameObject;
class Image;
//===================================================================End*/


//=======Resources所使用类,储存数据=======*/
//
//	object:指向数据的指针
//	kind:辨识数据类型	
//
class ResourcesModule
{
public:
	void* object;
	int kind;
};
//===================================================================End*/


//=======renderedTexture所使用类,储存当前所有即将渲染的物体信息=======*/

class AnimationInfo;

//类主体*/
//
//	animationInfo:每个渲染物体的不同动画的信息
//	rect:渲染物体的位置和大小
//	datumPoint:坐标基准点,渲染时使用,该基准点处于固定位置
//	scale:对大小的放缩,若scale=2,则大小变为2倍
//
//	alpha:渲染物体透明度
//	animationName:渲染物体需要渲染的动画名称,选择动画
//	imageFlip:翻转图片方式,水平翻转/垂直翻转/不翻转
//
//	beforeTimePoint:记录上一次渲染时间
//	indexTexture:即将渲染的纹理数组 下标
//	intervalTime:由动画速度确定的渲染间隔时间
//
class RenderObject
{
public:
	map < const char*, AnimationInfo > animationInfo;
	SDL_Rect rect;
	int datumPoint;
	double scale;

	int alpha;						//图片透明度
	const char* animationName;		//选择进行渲染的动画
	SDL_RendererFlip imageFlip;		//翻转图片


	//动画
	std::chrono::steady_clock::time_point beforeTimePoint;
	unsigned int indexTexture;									
	std::chrono::duration<double> intervalTime;				//两个渲染间的间隔时间

	RenderObject();
};

//动画信息*/
//
//	vectorSurface:储存生成图片时创建的surface,指针
//	vectorTexture:储存由surface生成的texture
//	animationLoop:该动画是否循环播放
//	animationEnd:该动画是否到达结尾,用于处理非循环播放的动画
//
class AnimationInfo
{
public:
	vector<SDL_Surface*>* vectorSurface;
	vector<SDL_Texture*> vectorTexture;
	BOOL animationLoop;				//是否循环播放
	BOOL animationEnd;				//到达动画结尾
};
//===================================================================End*/


//=======游戏组件类,所有游戏物体都应由此开始,该类包含所有游戏物体应持有的信息=======*/
class Image;

//
//	name:组件名称
//	rect:大小和位置,位置基于窗口左上基准点
//	scale:放缩大小
//	datumPoint:坐标基准点,该基准点处于固定位置
//
//	images:一个游戏组件可包含多个动画,每个动画有各自的属性
//
//	Present():将组件添加进渲染区
//	AddImage():将 已初始化完成 的Image类添加进组件
//
//	SetSize(int w, int h):以宽高设定大小
//	SetSize(double scale):以放缩程度设定大小
//	SetPosition():基于窗口左上设定坐标
//	SetDatumPoint():设定基准点,应使用_Card_DatumPoint_...作为参数,基准点定义见上
//
//	SetImageAlpha():设置所有动画的透明度
//	SetAnimationSpeed():设置所有动画的速度
//	ChooseAnimation():选择播放的动画和该动画是否翻转
//	SetAnimationLoop():设置指定动画是否循环播放
//	SetAnimationReplay():指定动画重新播放
//
//	GetAnimationEndState():获取指定动画是否到达结尾
//
class GameObject
{
public:
	const char* name;				//名字
	SDL_Rect rect;					//大小和位置
	double scale;					//缩放程度
	int datumPoint;					//坐标基准点

	map<const char*, Image*> images;

	GameObject();
	GameObject(const char* name);

	void Present();
	void AddImage(Image& image);

	void SetSize(int w, int h);
	void SetSize(double scale);
	void SetPosition(int x, int y);
	void SetDatumPoint(int datumPointChoice);

	void SetImageAlpha(int alpha);
	void SetAnimationSpeed(double speed);
	void ChooseAnimation(Image& animation, SDL_RendererFlip rendererFlip = SDL_FLIP_NONE);
	void SetAnimationLoop(Image& animation, BOOL loop);
	void SetAnimationReplay(Image& animation);

	BOOL GetAnimationEndState(Image& animation);
};
//===================================================================End*/


//=======图片/动画类=======*/
//
//	gameObjectName:附属于哪一个游戏组件,不推荐使用
//
//	Load():从相对路径加载图片,当多次使用时,自动将多张图片处理为动画,动画帧序列顺序取决于Load()的执行顺序
//
//	其他见GameObject类
//
class Image
{
public:
	const char* name;
	const char* gameObjectName;

	vector<SDL_Surface*> vectorSurface;

	unsigned int imageAlpha;		//图片透明度
	double animationSpeed;
	BOOL animationLoop;				//是否循环播放
	BOOL animationEnd;				//到达动画结尾


	Image();
	Image(const char* name);

	void Load(const char* filePath);

	void SetAlpha(int alpha);
	void SetAnimationSpeed(double speed);
};
//===================================================================End*/


//=======TODE:文字=======*/
class Text :public Image
{
public:
	const char* fontName;			//字体名称
	SDL_Rect fontRect;				//字体位置和大小
	unsigned int fontAlpha;			//字体透明度

	Text();
};
//===================================================================End*/


//=======FPS=======*/
//
//	interval:储存每两次处理的时间间隔,避免重复计算
//
class FPS :public Text
{
public:
	unsigned int value;				//FPS大小
	std::chrono::duration<double> interval;

	FPS();
};
//===================================================================End*/



//=======系统模块，使用引擎时不应接触=======*/
class SystemModule
{
private:
	HINSTANCE hInstance;			//窗口句柄
	SDL_Window* pWindow;			//窗口
	SDL_Renderer* pRenderer;		//渲染器
	TTF_Font* pDefaultFont;			//默认字体
	SDL_Event event;				//事件处理

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
//===================================================================End*/


//=======用户模块，引擎使用者可随意设置=======*/
class UserModule
{
public:
	const char* title;				//窗口标题
	SIZE windowSize;				//窗口大小
	FPS FPS;						//FPS
	//TODO://BOOL showFPS;			//是否显示FPS

	UserModule();
};
//===================================================================End*/


//=======引擎模块,统一管理system和user=======*/
class EngineModule :public UserModule
{
public:
	SystemModule system;

	EngineModule();
};
//===================================================================End*/
