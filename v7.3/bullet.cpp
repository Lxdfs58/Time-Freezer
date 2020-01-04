#include "bullet.h"
#include "resource.h"
bullet::bullet(int x, int y, Direction dir)
    : entity(10, 10, x, y), direction(dir)
{
    type=ENTITY_TYPE_BULLET;
    Health=0;
}

void bullet::setposition(int player_posX,int player_posY)
{
	PosX=player_posX;
	PosY=player_posY;
}

void bullet::move(int Vx , int Vy)
{
	switch( direction )
    {
    case DIR_CENTRE:
        DiffX = 0;
	    if(Vy)
		    DiffY=Vy>0? -Vy*2 :Vy*2;
	    else
		    DiffY=Vx>0? -Vx*2 :Vx*2;
        break;
 
    case DIR_LEFT:
        DiffX = DiffY/4;
	    if(Vy)
		    DiffY=Vy>0? -Vy*2 :Vy*2;
	    else
		    DiffY=Vx>0? -Vx*2 :Vx*2;
        break;
 
    case DIR_RIGHT:
        DiffX = -DiffY/4;
	    if(Vy)
		    DiffY=Vy>0? -Vy*2 :Vy*2;
	    else
		    DiffY=Vx>0? -Vx*2 :Vx*2;
        break;

    case DIR_StraighLEFT:
	    if(Vx||Vy) {
		    DiffX = -8;
		    DiffY =Vy;
	    }
	    else{
	    	DiffY = 0;
	    	DiffX = 0;
	    }
	    break;

    case DIR_StraighRIGHT:
	    if(Vx||Vy) {
		    DiffX = 8;
		    DiffY =Vy;
	    }
	    else{
		    DiffY = 0;
		    DiffX = 0;
	    }
	    break;
    }


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
