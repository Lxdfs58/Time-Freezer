#include "enemy.h"
#include "resource.h"

Enemy::Enemy(int randmax)
{
	static int num =1;
	ID = num;
	num++;
	explosionframe =0 ;
	frame = 0;
	creature = (randmax/7)%3+1;//1 for shark 2 for troodon 3 for fish
	color =1;//1 for black 2 for blue 3 for orange
	direction = (randmax/7)%4+1;
	count = 0;
	type=ENTITY_TYPE_ENEMY;
    isoutdated=false;
    int currentvel = vel+resource::score/5;
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
		Width = 74;
		Height =183;
		Health=3;
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
		Health=5;
	}
	else if(creature == 3) {
		Width = 43;
		Height =57;
		SplitClips[0].x = 0;
		SplitClips[0].y = 0;
		SplitClips[0].w = Width;
		SplitClips[0].h = Height;
		SplitClips[1].x = 0;
		SplitClips[1].y = 57;
		SplitClips[1].w = Width;
		SplitClips[1].h = Height;
		Health=1;
	}
	if(direction == 1)//forward
	{
		PosX = randmax%(resource::SCREEN_WIDTH - Width);
		PosY = resource::SCREEN_HEIGHT;
		rendx = PosX;
		rendy = PosY;
		DiffY = -currentvel;
		DiffX = 0;
		angle = 0;
	}
	else if(direction == 2)//backward
	{
		PosX = randmax%(resource::SCREEN_WIDTH - Width);
		PosY = -Height;
		rendx = PosX;
		rendy = PosY;
		DiffY = currentvel;
		DiffX = 0;
		angle = 180;
	}
	else if(direction == 3)//left
	{
		PosX = resource::SCREEN_WIDTH;
		PosY = randmax%(resource::SCREEN_HEIGHT - Width);
		rendx = PosX+(Height-Width)/2;
		rendy = PosY-(Height-Width)/2;
		int tem = Width;
		Width = Height;
		Height = tem;
		DiffY = 0;
		DiffX = -currentvel;
		angle = 270;
	}
	else if(direction == 4)//right
	{
		PosX = -Width;
		PosY = randmax%(resource::SCREEN_HEIGHT - Height);
		rendx = PosX+(Height-Width)/2;
		rendy = PosY-(Height-Width)/2;
		int tem = Width;
		Width = Height;
		Height = tem;
		DiffX = currentvel;
		DiffY =0;
		angle = 90;
	}
	if(randmax%7 == 0) {
		color = 2;
		Health*=2;
	}
	localscore = Health;
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
	rendx += DiffX;
	rendy += DiffY;
	isupdate=true;
	}
}

void Enemy::offset(int Dx , int Dy)
{
	// Just like the move function but not modify the position difference.
	PosX += Dx;
	PosY += Dy;
	rendx += Dx;
	rendy += Dy;
}

void Enemy::onCollision(entity *another)
{
	switch( another->GetType() )
	{
    case ENTITY_TYPE_PLAYER:
    	if(another->Health==1)
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
        if(creature == 1 && color == 1)
            resource::sharkTexture.render(rendx ,rendy ,NULL,angle);
        else if(creature == 2 && color == 1)
            resource::troodonTexture.render(rendx ,rendy ,&SplitClips[frame],angle);
        else if(creature == 3 && color == 1)
            resource::fishTexture.render(rendx ,rendy ,&SplitClips[frame],angle);
        else if(creature == 1 && color == 2)
            resource::bluesharkTexture.render(rendx ,rendy ,NULL,angle);
        else if(creature == 2 && color == 2)
            resource::bluetroodonTexture.render(rendx ,rendy ,&SplitClips[frame],angle);
        else if(creature == 3 && color == 2)
            resource::bluefishTexture.render(rendx ,rendy ,&SplitClips[frame],angle);
        //SDL_Rect rect = { .x=PosX, .y=PosY, .w=getWidth(), .h=getHeight() };
        //SDL_RenderDrawRect(resource::gRenderer, &rect);
    }
	else if(!isoutdated){
		stringstream AddScore;
		AddScore.str( "" );
		AddScore<<"+ "<<localscore;
		//Render adding score
		SDL_Color textColor = { 255, 255, 255  };
		if( !resource::scoreTexture.loadFromRenderedText( AddScore.str().c_str(), textColor ) )
		{
			printf( "Unable to render score texture!\n" );
		}
		resource::scoreTexture.render(resource::SCREEN_WIDTH - resource::gTextTexture.getWidth()+75  , 30);

		static int deadPosX;
		static int deadPosY;
		if(Width||Height) {
			deadPosX = PosX + (Width - 128) / 2;
			deadPosY = PosY + (Height - 128) / 2;
		}
		resource::explosionTexture.render(deadPosX ,deadPosY ,&Explosion[explosionframe/5]);
		Width = 0;//prevent to collide with explosion
		Height =0;
		DiffY = 0;
		DiffX = 0;
		Health = 0;
		cout<<"ID :"<<ID<<" x "<<PosX<<" y "<<PosY<<"  ####killed"<<endl;
		cout<<"current frame "<<explosionframe<<endl;
		if(explosionframe/5==11){
			isoutdated =true;
			Health = -1;
		}
		if(explosionframe == 5){
			MusicPlayer explode;
			explode.Play("../textures/Explosion.wav");
			(resource::score)+=localscore;
		}
		explosionframe++;
	}
	
}
