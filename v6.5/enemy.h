#ifndef V3_5_REFINED_ENEMY_H
#define V3_5_REFINED_ENEMY_H

#include "entity.h"

class Enemy : public entity{
public:
	//Initialize  randomly
	Enemy(int randmax);

	~Enemy();
	void move(int dx,int dy);
	
	void onCollision(entity *another);

	void update();

	void render();

	static const int vel = 3;
private:
	SDL_Rect SplitClips[3];
	SDL_Rect Explosion[15];
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
    bool isupdate;
    
    int i;
    //ID
    int ID;
    
    bool isoutdated;
};


#endif 
