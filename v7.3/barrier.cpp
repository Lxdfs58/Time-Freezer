//
// Created by Davis Chou on 2019/12/25.
//
#include "resource.h"
#include "barrier.h"

barrier::barrier(int x, int y)
    : entity(resource::BARRIER_WIDTH, resource::BARRIER_HEIGHT, x, y)
{
	type=ENTITY_TYPE_BARRIER;
	Health = 10;
/*	isoutdated=false;
	explosion = &resource::explosionTexture;
	for(int i=0;i<4;i++)
	{
	   Explosion[i].x = 25+115*i;
	   Explosion[i].y = 40;
	   Explosion[i].w = 75;
	   Explosion[i].x = 75;  		
	}
	for(int i=4;i<8;i++)
	{
	   Explosion[i].x = 16+129*i;
	   Explosion[i].y = 150;
	   Explosion[i].w = 89;
	   Explosion[i].x = 89;  		
	}
	for(int i=8;i<12;i++)
	{
	   Explosion[i].x = 16+129*i;
	   Explosion[i].y = 285;
	   Explosion[i].w = 89;
	   Explosion[i].x = 89;  		
	}
	for(int i=12;i<16;i++)
	{
	   Explosion[i].x = 16+129*i;
	   Explosion[i].y = 414;
	   Explosion[i].w = 89;
	   Explosion[i].x = 89;  		
	}*/
	
	
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
	if(Health>-1)
		resource::rockTexture.render(PosX,PosY);
/*	if(isoutdated==false&&Health<=0)
	{
		for(int i=0;i<16;i++)
	   {
	   	    cout<<"explosion"<<endl;
			resource::explosionTexture.render(PosX ,PosY ,&Explosion[i]);
	   }
	   isoutdated=true;
	}*/
}
