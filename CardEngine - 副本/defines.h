#pragma once

#ifdef UNICODE
#define SetWindowText  SetWindowTextW
#else
#define SetWindowText  SetWindowTextA
#endif

#define _Card_DefaultTitle "CardEngine"
#define _Card_CardEngine "-CardEngine"
#define _Card_DefaultFontSize 24


#define _Card_GameObject 1
#define _Card_Image 2

#define _Card_UpperLeft 1
#define _Card_BottomLeft 2