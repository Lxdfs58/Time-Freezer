#ifndef PLAYER_H
#define PLAYER_H
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include "entity.h"
#include "Ltexture.h"
#include "barrier.h"

class player : public entity
{
public:
	player(int x, int y, int k);
	~player();

	void update();
    void move(int Dx , int Dy);
	void render();
    void reset(int posX,int posY);
	static const int WALKING_ANIMATION_FRAMES = 6;
	SDL_Rect SplitClips[WALKING_ANIMATION_FRAMES];
	
	

public:
    static const int WIDTH  = 80;
    static const int HEIGHT = 200;

private:
	//current frame
	int frame;
	//type of player
	int kind;
	unsigned int count;
	SDL_Rect Explosion[15];
	bool isoutdated;
	int ExplosionFrame;
	
};
#endif
