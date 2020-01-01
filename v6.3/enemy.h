#ifndef V3_5_REFINED_ENEMY_H
#define V3_5_REFINED_ENEMY_H

#include "entity.h"

class Enemy : public entity{
public:
	//Initialize the enemy
	//Enemy();
	//Initialize  randomly
	Enemy(int randmax);

	void move(int dx,int dy);
	
	void onCollision(entity *another);

	void update();

	void render();

	static const int vel = 8;
private:
	SDL_Rect SplitClips[2];
	//colors
	int color;
	int direction;
	int creature;
	//current frame
	int frame;
	unsigned int count;
	//flip angle
	double angle;
	//Local texture
	LTexture *local;
    bool isupdate;
};


#endif 
