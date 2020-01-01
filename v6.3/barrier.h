//
// Created by Davis Chou on 2019/12/25.
//
#ifndef V2_PLAYER_BARRIER_H
#define V2_PLAYER_BARRIER_H

#include "entity.h"

class barrier : public entity
{
public:
	barrier(int x, int y);

	void onCollision(entity *another);

	bool OutOfScreen();
	void move(int Dx,int Dy);
	void render();
};
#endif
