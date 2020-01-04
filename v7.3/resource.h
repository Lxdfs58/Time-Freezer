#ifndef RESOURCE_H_
#define RESOURCE_H_

#include <SDL_ttf.h>
#include "Ltexture.h"

class resource
{
public:
	static const int SCREEN_WIDTH = 640;
	static const int SCREEN_HEIGHT = 800;

	static const int BARRIER_WIDTH = 120;
	static const int BARRIER_HEIGHT = 80;
	static const int BARRIER_Y_DISTANCE = 260;

	static int score;
	static long long distance;

    static SDL_Window *gWindow;
    static SDL_Renderer *gRenderer;
    static TTF_Font *gFont;


	static LTexture gElephantTexture;
	static LTexture gCowTexture;
	static LTexture gWolfTexture;
	static LTexture gBGTexture;
	static LTexture rockTexture;
	static LTexture menuTexture;
	static LTexture bulletTexture; 
	
	static LTexture sharkTexture;
	static LTexture bluesharkTexture;
	
    static LTexture troodonTexture;
    static LTexture bluetroodonTexture;
    
    static LTexture fishTexture;
    static LTexture bluefishTexture;
    
	static LTexture gTextTexture;
	static LTexture scoreTexture;
	static LTexture explosionTexture;
	static LTexture gameoverTexture;
	static LTexture restartTexture;
};

#endif
