#ifndef BULLET_H
#define BULLET_H

#include <SDL2/SDL.h>
#include "entity.h"

class bullet : public entity
{
public:
    enum Direction
    {
        DIR_CENTRE,
        DIR_LEFT,
        DIR_RIGHT,
        DIR_StraighLEFT,
	    DIR_StraighRIGHT,
    };	
public:
	bullet(int x, int y, Direction dir = DIR_CENTRE);

	void setposition(int player_posX,int player_posY);
	void move(int Vx , int Vy);
	void render();
	void onCollision(entity *another);

private:
    Direction direction;

};
#endif
