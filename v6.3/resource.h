#ifndef RESOURCE_H_
#define RESOURCE_H_

#include <SDL_ttf.h>
#include "Ltexture.h"

class resource
{
public:
	static const int SCREEN_WIDTH = 640;
	static const int SCREEN_HEIGHT = 800;

	static const int BARRIER_WIDTH = 50;
	static const int BARRIER_Y_DISTANCE = 260;

	static int score;

    static SDL_Window *gWindow;
    static SDL_Renderer *gRenderer;
    static TTF_Font *gFont;


	static LTexture gDotTexture;
	static LTexture gBGTexture;
	static LTexture rockTexture;
	static LTexture menuTexture;
	static LTexture bulletTexture; //�l�utexture �bprocedures.cpp�̹�@
	static LTexture sharkTexture;
    static LTexture troodonTexture;
    static LTexture fishTexture;
	static LTexture gTextTexture;
	static LTexture scoreTexture;
};

#endif
