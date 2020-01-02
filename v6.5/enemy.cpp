#include "enemy.h"
#include "resource.h"
#include "MusicPlayer.h"
Enemy::Enemy(int randmax)
{
	static int num =1;
	ID = num;
	num++;
	i =0 ;
	frame = 0;
	creature = (randmax/7)%3+1;
	color = randmax%3+1;//1 for black 2 for blue 3 for orange
	direction = (randmax/7)%4+1;
	count = 0;
	type=ENTITY_TYPE_ENEMY;
    isoutdated=false;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<4;j++){
			Explosion[i*4+j].x = 128*j;
			Explosion[i*4+j].y = 128*i;
			Explosion[i*4+j].w = 128;
			Explosion[i*4+j].h = 128;
		}
	}
	if(creature == 1) {
		Width = 147;
		Height =363;
		Health=5;
	}
	else if(creature == 2) {
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

Enemy::~Enemy()
{

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
	}
	else if(!isoutdated){
		DiffY = 0;
		DiffX = 0;
		resource::explosionTexture.render(PosX+(Width-128)/2,PosY + (Height-128)/2,&Explosion[i]);
		i++;
		Health = 0;
		cout<<"ID :"<<ID<<" x "<<PosX<<" y "<<PosY<<"  ####killed"<<endl;
		cout<<"current frame "<<i<<endl;
		if(i==11){
			isoutdated =true;
			Health = -1;
		}
		if(i == 5){
			MusicPlayer explode;
			explode.Play("../textures/Explosion.mp3");
			(resource::score)++;
		}
	}
	
}
