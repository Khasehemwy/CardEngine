#pragma once



/*-------����ϵͳ-------*/
GameModule* Card_Initial(HINSTANCE);

void Card_HandleError();

void Card_HandleEvent(GameModule*);

void Card_Run(GameModule*);

void Card_SetTitle(GameModule*, const char*);

void Card_SetWindowSize(GameModule*, SIZE*);


/*-------����ͼƬ-------*/
void Card_LoadImage(const char*, const char*);

void Card_PresentImage(GameModule*, const char*);



/*-------������Ⱦ-------*/
void Card_RenderPresent(GameModule*);

void Card_MoveObject(const char*, int , int );

void Card_SetSizeObject(const char*, int, int);