#include "wideshooting.h"
#include "resource.h"
//wideshooting::wideshooting()
//{type=ENTITY_WIDESHOOTING;}

void wideshooting::setposition(int player_posX,int player_posY)
{
	a->setposition(player_posX, player_posY);
	b->setposition(player_posX, player_posY);
	c->setposition(player_posX, player_posY);
}

void wideshooting::move(int Vx , int Vy)
{
    DiffX = 0;

    if(Vy)
	DiffY=Vy>0? -Vy*2 :Vy*2;
    else
	DiffY=Vx>0? -Vx*2 :Vx*2;
    a->move(Vx,Vy);
    b->move(Vy,Vy);
    c->move(-Vy,Vy);
	//a.PosX += DiffX;
	//a.PosY += DiffY;

	
	//cout<<"score="<<score<<endl;
}

void wideshooting::render()
{
  	a->render();
	b->render();
    c->render();
}
void wideshooting::onCollision(entity * other)
{
a->onCollision( other);
b->onCollision( other);
c->onCollision( other);
}
