# CardEngine
游戏2D动画系统

# 展示
![站立](https://user-images.githubusercontent.com/57032017/113245645-f3305b80-92e9-11eb-92df-d5a9f0c01239.gif)
![行走](https://user-images.githubusercontent.com/57032017/113245878-6e920d00-92ea-11eb-84ff-01786895290b.gif)

![烟花](https://user-images.githubusercontent.com/57032017/113246014-bca71080-92ea-11eb-9350-bbbbbab66f92.gif)

# 功能
采用**精灵动画**技术，把一系列静态2D图片不断快速地在屏幕绘制，以产生动感。

该动画系统可添加一系列图片(.jpg/.png等文件)，并自动生成动画。
可设置：FPS，图片大小/透明度，动画速度，动画是否循环播放等功能。

该动画系统类似Unity分为Start()和Update()函数，Update使用多线程，避免消息传递的阻塞。
