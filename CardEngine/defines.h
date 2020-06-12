#pragma once

#ifdef UNICODE
#define SetWindowText  SetWindowTextW
#else
#define SetWindowText  SetWindowTextA
#endif

#define _DefaultTitle "CardEngine"
#define _CardEngine "-CardEngine"
#define _DefaultFontSize 24


#define _Image "IMAGE" 