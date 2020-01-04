#ifndef BULLET_H
#define BULLET_H

#include <SDL2/SDL.h>
#include "entity.h"

class bullet : public entity
{
public:
	bullet(int x, int y);

	void setposition(int player_posX,int player_posY);
	void move(int Vx , int Vy);
	void render();
	void onCollision(entity *another);

};
#endif
