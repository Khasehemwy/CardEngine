#pragma once




GameModule* Card_Initial(HINSTANCE);

void Card_HandleError();

void Card_HandleEvent(GameModule*);

void Card_Run(GameModule*);

void Card_SetTitle(GameModule*, string*);

void Card_SetWindowSize(GameModule*, SIZE*);

void Card_LoadImage(string*, string*);