#include "bullet.h"
#include "resource.h"
bullet::bullet(int x, int y)
    : entity(10, 10, x, y)
{
	type=ENTITY_TYPE_BULLET;
	Health=1;
}

void bullet::setposition(int player_posX,int player_posY)
{
	PosX=player_posX;
	PosY=player_posY;
}

void bullet::move(int Vx , int Vy)
{
    DiffX = 0;

    if(Vy)
	DiffY=Vy>0? -Vy*2 :Vy*2;
    else
	DiffY=Vx>0? -Vx*2 :Vx*2;

	PosX += DiffX;
	PosY += DiffY;
	
	//cout<<"score="<<score<<endl;
}

void bullet::render()
{
    if(Health>-1)
	resource::bulletTexture.render( PosX, PosY);
}

void bullet::onCollision(entity *another)
{
	switch( another->GetType() )
	{
    case ENTITY_TYPE_ENEMY:
    	//if(another->Health<=-1) (resource::score)++;
    	cout<<"score="<<resource::score<<endl;
		break;

	default:
		break;
	}
}
