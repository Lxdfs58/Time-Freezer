#include "enemy.h"
#include "resource.h"
Enemy::Enemy(int randmax)
{
	creature = (randmax/7)%3+1;
	color = randmax%3+1;//1 for black 2 for blue 3 for orange
	direction = (randmax/7)%4+1;
	count = 0;
	type=ENTITY_TYPE_ENEMY;
	if(creature == 1) {
		local = &resource::sharkTexture;
		Width = 147;
		Height =363;
		Health=5;
	}
	else if(creature == 2) {
		local = &resource::troodonTexture;
		Width = 80;
		Height =355;
		SplitClips[0].x = 25;
		SplitClips[0].y = 132;
		SplitClips[0].w = Width;
		SplitClips[0].h = Height;
		SplitClips[1].x = 25;
		SplitClips[1].y = 761;
		SplitClips[1].w = Width;
		SplitClips[1].h = Height;
		Health=3;
	}
	else if(creature == 3) {
		local = &resource::fishTexture;
		Width = 123;
		Height =170;
		SplitClips[0].x = 12;
		SplitClips[0].y = 302;
		SplitClips[0].w = Width;
		SplitClips[0].h = Height;
		SplitClips[1].x = 8;
		SplitClips[1].y = 772;
		SplitClips[1].w = Width;
		SplitClips[1].h = Height;
		Health=1;
	}

	if(color == 1)
	{
		local->setColor(80,80,80);
	}
	else if(color == 2)
	{
		local->setColor(0,50,255);
	}
	else if(color == 3)
	{
		local->setColor(255,170,0);
	}
	cout<<direction<<endl;
	if(direction == 1)//forward
	{
		PosX = randmax%(resource::SCREEN_WIDTH - Width);
		PosY = resource::SCREEN_HEIGHT;
		DiffY = -vel;
		DiffX = 0;
		angle = 0;
	}
	else if(direction == 2)//backward
	{
		PosX = randmax%(resource::SCREEN_WIDTH - Width);
		PosY = -Height;
		DiffY = vel;
		DiffX = 0;
		angle = 180;
	}
	else if(direction == 3)//left
	{
		PosX = resource::SCREEN_WIDTH;
		PosY = randmax%(resource::SCREEN_HEIGHT - Width);
		DiffY = 0;
		DiffX = -vel;
		angle = 270;
	}
	else if(direction == 4)//right
	{
		PosX = -Width;
		PosY = randmax%(resource::SCREEN_HEIGHT - Height);
		DiffX = vel;
		angle = 90;
	}
	
}

void Enemy::move(int dx,int dy)
{
	isupdate=false;
	if(dx||dy)
	{
	PosX += DiffX;
	PosY += DiffY;
	isupdate=true;
	}
	
	//cout<<'x'<<PosX<<'y'<<PosY<<endl;
}

void Enemy::onCollision(entity *another)
{
	switch( another->GetType() )
	{
    case ENTITY_TYPE_PLAYER:
    	another->Health--;
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
	
void Enemy::update()
{
	if(isupdate)
	{
	frame = (count/10)%2;
	count++;
	if(count>10000)
	count = 0;
	}
	
}

void Enemy::render()
{
	if(creature == 1&&Health>0)
		resource::sharkTexture.render(PosX ,PosY ,NULL,angle);
	else if(creature == 2&&Health>0)
		resource::troodonTexture.render(PosX ,PosY ,&SplitClips[frame],angle);
	else if(creature == 3&&Health>0)
		resource::fishTexture.render(PosX ,PosY ,&SplitClips[frame],angle);
}
