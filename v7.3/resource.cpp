#include "resource.h"

int resource::score;

SDL_Window* resource::gWindow = NULL;
SDL_Renderer* resource::gRenderer = NULL;
TTF_Font* resource::gFont = NULL;


LTexture resource::gDotTexture;
LTexture resource::gBGTexture;
LTexture resource::rockTexture;
LTexture resource::menuTexture;
LTexture resource::bulletTexture;
LTexture resource::sharkTexture;
LTexture resource::bluesharkTexture;

LTexture resource::troodonTexture;
LTexture resource::bluetroodonTexture;

LTexture resource::fishTexture;
LTexture resource::bluefishTexture;

LTexture resource::explosionTexture;
LTexture resource::gameoverTexture;  
LTexture resource::restartTexture; 

LTexture resource::gTextTexture;
LTexture resource::scoreTexture;
