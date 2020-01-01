#include "resource.h"
#include "player.h"

player::player(int x, int y)
    : entity(WIDTH, HEIGHT, x, y)
{
	type=ENTITY_TYPE_PLAYER;
	
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
	else if(DiffX == 0 && DiffY == 0)
		frame = 0;
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
	resource::gDotTexture.render(PosX, PosY, &SplitClips[frame]);
}
