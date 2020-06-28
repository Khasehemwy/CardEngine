#pragma once

//设定编码,推荐Unicode*/
#ifdef UNICODE
#define SetWindowText  SetWindowTextW
#else
#define SetWindowText  SetWindowTextA
#endif

//默认窗口标题*/
#define _Card_DefaultTitle "CardEngine"

//窗口标题后缀,若用户设置标题为Game,则实际窗口标题为 Game-CardEngine */
#define _Card_CardEngine "-CardEngine"

//默认字体大小*/
#define _Card_DefaultFontSize 24

//辨识Resources种类,Resources见function.cpp*/
#define _Card_GameObject 1
#define _Card_Image 2

//辨识坐标基准点设定*/
#define _Card_DatumPoint_UpperLeft 1
#define _Card_DatumPoint_BottomLeft 2
#define _Card_DatumPoint_Center 3

//辨识特殊大小设定*/
#define _Card_Size_FullWindow -1.0