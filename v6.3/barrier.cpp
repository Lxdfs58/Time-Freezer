//
// Created by Davis Chou on 2019/12/25.
//
#include "resource.h"
#include "barrier.h"

barrier::barrier(int x, int y)
    : entity(resource::BARRIER_WIDTH, resource::BARRIER_WIDTH, x, y)
{
	type=ENTITY_TYPE_BARRIER;
	Health = 10;
}

void barrier::onCollision(entity *another)
{
    switch( another->GetType() )
	{
    case ENTITY_TYPE_PLAYER:
    	another->offset(-another->getDiffX(), -another->getDiffY());
		break;
    case ENTITY_TYPE_BULLET:
		another->offset(-another->getDiffX(), -another->getDiffY());
		Health--;
		another->Health--;
		break;
		
	default:
		break;
	}
}

bool barrier::OutOfScreen()
{
	return PosY > resource::SCREEN_HEIGHT*2;
}

void barrier::move(int Dx , int Dy)
{
	DiffX = 0;
    DiffY = 0;

    PosX += DiffX;
    PosY += DiffY;
}

void barrier::render()
{
	if(Health>0)
		resource::rockTexture.render(PosX,PosY);
}
