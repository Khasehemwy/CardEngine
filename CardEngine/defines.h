#pragma once

#ifdef UNICODE
#define SetWindowText  SetWindowTextW
#else
#define SetWindowText  SetWindowTextA
#endif

#define DefaultTitle "CardEngine"
#define CardEngine "-CardEngine"
#define DefaultFontSize 24