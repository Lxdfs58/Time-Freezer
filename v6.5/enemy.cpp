#include "enemy.h"
#include "resource.h"
Enemy::Enemy(int randmax)
{
	i = 1;
	creature = (randmax/7)%3+1;
	color = randmax%3+1;//1 for black 2 for blue 3 for orange
	direction = (randmax/7)%4+1;
	count = 0;
	type=ENTITY_TYPE_ENEMY;
    isoutdated=false;
	explosion = &resource::explosionTexture;
	for(int i=0;i<4;i++)
	{
	   Explosion[i].x = 25+115*i;
	   Explosion[i].y = 40;
	   Explosion[i].w = 75;
	   Explosion[i].h = 75;  		
	}
	for(int i=4;i<8;i++)
	{
	   Explosion[i].x = 16+129*i;
	   Explosion[i].y = 150;
	   Explosion[i].w = 89;
	   Explosion[i].h = 89;  		
	}
	for(int i=8;i<12;i++)
	{
	   Explosion[i].x = 16+129*i;
	   Explosion[i].y = 285;
	   Explosion[i].w = 89;
	   Explosion[i].h = 89;  		
	}
	for(int i=12;i<16;i++)
	{
	   Explosion[i].x = 16+129*i;
	   Explosion[i].y = 414;
	   Explosion[i].w = 89;
	   Explosion[i].h = 89;  		
	}
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
		DiffY =0;
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
	//static int i=0;
	if(Health>0){
		if(creature == 1)
			resource::sharkTexture.render(PosX ,PosY ,NULL,angle);
		else if(creature == 2)
			resource::troodonTexture.render(PosX ,PosY ,&SplitClips[frame],angle);
		else if(creature == 3)
			resource::fishTexture.render(PosX ,PosY ,&SplitClips[frame],angle);
		//cout<<'x'<<PosX<<'y'<<PosY<<"alive"<<endl;
	}
	else if(!isoutdated){
		DiffY = 0;
		DiffX = 0;
		resource::explosionTexture.render(PosX + Width/2,PosY + Height/2,&Explosion[i/10]);
		i++;
		if(i/10==15){
			isoutdated =true;
			Health = -1;
		}
		Health = 0;
		//cout<<'x'<<PosX<<'y'<<PosY<<"  ####killed"<<endl;
	}
	//cout<<'x'<<PosX<<'y'<<PosY<<endl;
	//cout<<"current frame "<<i<<endl;
	
}
