# CardEngine
游戏2D动画系统

# 展示
<image src="https://user-images.githubusercontent.com/57032017/113245645-f3305b80-92e9-11eb-92df-d5a9f0c01239.gif" size=60%></image>
<image src="https://user-images.githubusercontent.com/57032017/113245878-6e920d00-92ea-11eb-84ff-01786895290b.gif" size=60%></image>

<image src="https://user-images.githubusercontent.com/57032017/113246014-bca71080-92ea-11eb-9350-bbbbbab66f92.gif" size=60%></image>


# 功能
采用**精灵动画**技术，把一系列静态2D图片不断快速地在屏幕绘制，以产生动感。

该动画系统可添加一系列图片(.jpg/.png等文件)，并自动生成动画。
可设置：FPS，图片大小/透明度，图片基准点，动画速度，动画是否循环播放等功能。

该动画系统类似Unity分为Start()和Update()函数，Update使用多线程，避免消息传递时阻塞。

动画系统主要类：GameObject，具体功能：
```cpp
//=======游戏组件类,所有游戏物体都应由此开始,该类包含所有游戏物体应持有的信息=======*/

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
class GameObject;
```
