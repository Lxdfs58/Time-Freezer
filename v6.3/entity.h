#ifndef ENTITY_H
#define ENTITY_H

#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Ltexture.h"
#include "EntityType.h"
using namespace std;

class entity
{
public:
	entity();
	entity(int W ,int H ,int X ,int Y);
	virtual ~entity() {}

	int getWidth() const { return Width; }
	int getHeight() const { return Height; }

	int getPosX() const { return PosX; }
	int getPosY() const { return PosY; }

	int getDiffX() const { return DiffX; }
	int getDiffY() const { return DiffY; }
	
    EntityType GetType() const { return type; }
    
	virtual void render(){}
	virtual void move(int Dx , int Dy){}
	void offset(int Dx, int Dy);
	virtual void update() {}

	bool checkCollision(const entity *another);
	virtual void onCollision(entity *another) {}
    int Health;
protected:
	int Width;
	int Height;
	int PosX;
	int PosY;
	int DiffX;  // Difference from the last position.
	int DiffY;  //
    EntityType type;   
};
#endif
