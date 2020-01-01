//
// Created by Davis Chou on 2019/12/25.
//
#include "resource.h"
#include "procedures.h"
using namespace std;
bool init()
{
	bool success = true;

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		return false;
	}

    if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
    {
        printf( "Warning: Linear texture filtering not enabled!" );
    }

    resource::gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, resource::SCREEN_WIDTH, resource::SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( resource::gWindow == NULL )
    {
        printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
        return false;
    }

    resource::gRenderer = SDL_CreateRenderer( resource::gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if( resource::gRenderer == NULL )
    {
        printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
        return false;
    }

    SDL_SetRenderDrawColor( resource::gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        return false;
    }
    //Initialize SDL_ttf
	if( TTF_Init() == -1 )
	{
		printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}

    return true;
}


bool loadMedia()
{
	bool success = true;
	if( !resource::gDotTexture.loadFromFile("../textures/elephant.png" ) )
	{
		printf( "Failed to load walking animation texture!\n" );
		success = false;
	}
	if( !resource::gBGTexture.loadFromFile( "../textures/bg.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !resource::rockTexture.loadFromFile("../textures/rock.png") )
    {
        printf( "Failed to load rock texture!\n" );
        success = false;
    }
	if( !resource::menuTexture.loadFromFile( "../textures/menu.png" ) )
	{
		printf( "Failed to load menu texture!\n" );
		success = false;
	}
	if( !resource::bulletTexture.loadFromFile( "../textures/playerBullet.png" ) )
	{
		printf( "Failed to load bullet texture!\n" );
		success = false;
	}
	if( !resource::sharkTexture.loadFromFile( "../textures/shark.png" ) )
    {
        printf( "Failed to load shark texture!\n" );
        success = false;
    }
    if( !resource::troodonTexture.loadFromFile( "../textures/troodon.png" ) )
    {
        printf( "Failed to load troodon texture!\n" );
        success = false;
    }
    if( !resource::fishTexture.loadFromFile( "../textures/fish.png" ) )
    {
        printf( "Failed to load fish texture!\n" );
        success = false;
    }
    //Open the font
	resource::gFont = TTF_OpenFont( "../fonts/GenJyuuGothic-Heavy.ttf", 28 );//�r��j�p
	if( resource::gFont == NULL )
	{
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	else
	{
		//Render text
		SDL_Color textColor = { 0, 0, 0 };//(R,G,B) 
		if( !resource::gTextTexture.loadFromRenderedText( "high score:", textColor ) )
		{
			printf( "Failed to render text texture!\n" );
			success = false;
		}
	}
	
	return success;
}

void close()
{
	resource::gDotTexture.free();
	resource::gBGTexture.free();
	resource::rockTexture.free();
	resource::gTextTexture.free();
	resource::scoreTexture.free();
	resource::bulletTexture.free();
	resource::sharkTexture.free();
	resource::troodonTexture.free();
	resource::fishTexture.free();
	
	SDL_DestroyRenderer( resource::gRenderer );
	SDL_DestroyWindow( resource::gWindow );
	resource::gWindow = NULL;
	resource::gRenderer = NULL;
	TTF_CloseFont( resource::gFont );
	resource::gFont = NULL; 
	
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}


void handleEvent( SDL_Event& e ,int& VelX ,int& VelY)
{
	int VEL = 5;
	//If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
	{
		//Adjust the velocity
		//resource::startTime=SDL_GetTicks();
		switch( e.key.keysym.sym )
		{
			case SDLK_UP:
				VelX = 0;
				VelY -= VEL;
				break;
			case SDLK_DOWN:
				VelX = 0;
				VelY += VEL;
				break;
			case SDLK_LEFT:
				VelY = 0;
				VelX -= VEL;
				break;
			case SDLK_RIGHT:
				VelY = 0;
				VelX += VEL;
				break;
		}
		
	}
		//If a key was released
	else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
	{
		//Adjust the velocity
		switch( e.key.keysym.sym )
		{
			case SDLK_UP: VelY =0; break;
			case SDLK_DOWN: VelY =0; break;
			case SDLK_LEFT: VelX =0; break;
			case SDLK_RIGHT: VelX =0; break;
		}
	}
}
