#include "resource.h"
#include "player.h"
#include "MusicPlayer.h"
player::player(int x, int y)
    : entity(WIDTH, HEIGHT, x, y)
{
	type=ENTITY_TYPE_PLAYER;
	Health=1;
	//Initialize the frame
	frame = 0;
	//Initialize the clips
	for(int i=0;i<WALKING_ANIMATION_FRAMES;i++)
    {
        SplitClips[i].x = 140 + 367 * i;
        SplitClips[i].y = 52;
        SplitClips[i].w = Width;
        SplitClips[i].h = Height;
    }
    ExplosionFrame=0;
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

}

player::~player()
{
}

void player::update()
{
	//Frame changing
	if(DiffY > 0)
		frame = (count/10)%2;
	else if(DiffY <0)
		frame = (count/10)%2;

	if(DiffX > 0)
		frame = (count/10)%2+2;
	else if(DiffX <0)
		frame = (count/10)%2+4;
	//If the dot collided or went too far to the left or right
	if(PosX < 0 )
	{
		//Move back
		PosX -= DiffX;
		frame = (count/10)%2+4;
	}
	else if((PosX + Width) > resource::SCREEN_WIDTH){
		//Move back
		PosX -= DiffX;
		frame = (count/10)%2+2;
	}

	count = ( count + 1 ) % 1000;
}
void player::move(int Dx , int Dy)
{
	DiffX = Dx;
    DiffY = Dy;

    PosX += DiffX;
    PosY += DiffY;
}
void player::render()
{
#warning Debug code!
  //  SDL_Rect rect = { .x=PosX, .y=PosY, .w=getWidth(), .h=getHeight() };
  //  SDL_RenderDrawRect(resource::gRenderer, &rect);
#warning Temporary hide!
	if(Health==1)
	{
		resource::gDotTexture.render(PosX, PosY, &SplitClips[frame]);
	}
	else if(Health==0 && !isoutdated){

		resource::explosionTexture.render(PosX+(Width-128)/2,PosY + (Height-128)/2,&Explosion[ExplosionFrame]);
		ExplosionFrame++;
		cout<<"current frame "<<ExplosionFrame<<endl;
		if(ExplosionFrame == 5){
			MusicPlayer explode;
			explode.Play("../textures/Explosion.wav");
		}
		if(ExplosionFrame==11){
			isoutdated =true;
			Health = -1;
		}
	}
	
}
void player::reset(int posX,int posY)
{
	PosX=posX;
	PosY=posY;
	frame = 0;
	isoutdated=false;
	ExplosionFrame=0;
}
