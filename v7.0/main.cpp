#include "procedures.h"
#include "MusicPlayer.h"

using namespace std;

int main( int argc, char* args[] )
{
    try
    {
        srand(time(NULL));

        if( !init() )
            throw runtime_error("Failed to initialize!");

		if( !loadMedia() )
			throw runtime_error("Failed to load media!");

        int playerOriginX = ( resource::SCREEN_WIDTH - player::WIDTH )/2;
        int playerOriginY = resource::SCREEN_HEIGHT - 1.5 * player::HEIGHT;
        
		player elephant(playerOriginX, playerOriginY);
		
        MusicPlayer musicPlayer;
        
        Timer bulletTimer(800);
        resource::score = 0;

        list<shared_ptr<entity> > pool;
        BarrierGenerator barrierGenerator(&pool);
        EnemyGenerator enemyGenerator(&pool);
        
        std::stringstream scoreText; 
		int scrollingOffset = 0;
		//Variables that records the current velocity
		int Vx=0,Vy=0;
		bool menu =true;
        bool quit = false;
		while( !quit )
		{
		    SDL_Event e;
			while( SDL_PollEvent( &e ) != 0 )
			{
				if( e.type == SDL_QUIT )
				{
					quit = true;
				}
				if( e.type == SDL_KEYDOWN)
                {
                    switch( e.key.keysym.sym )
                    {   
                        case SDLK_SPACE:
                        	if(elephant.Health<1&& !menu){
		                        menu = true;
		                        cout<<"restart"<<endl;
		                        break;
                        	}
                            menu = false;
                            elephant.Health=1;
                            resource::score=0;
                            break;
                    }
                }
                /*if( e.type == SDL_KEYDOWN && elephant.Health<1 && !menu)
                {
                    switch( e.key.keysym.sym )
                    {   
                        case SDLK_SPACE:
                            menu = true;
                            break;
                    }
                }*/
				handleEvent( e ,Vx ,Vy);
			}

			//Clear screen
			SDL_SetRenderDrawColor( resource::gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
			SDL_RenderClear( resource::gRenderer );
            if(menu)
            {
	            resource::distance = 0;
            	resource::menuTexture.render(0,0);
            	elephant.reset(playerOriginX, playerOriginY);
            	elephant.render();
            	scoreText.str( "" );
                scoreText<<resource::score;
                //Render text
                SDL_Color textColor = { 0, 0, 0 };
                if( !resource::scoreTexture.loadFromRenderedText( scoreText.str().c_str(), textColor ) )
                {
                    printf( "Unable to render score texture!\n" );
                }
                resource::scoreTexture.render(( resource::SCREEN_WIDTH /2-10  ) , 710);
	            for(auto iter = pool.begin(); iter != pool.end();)
	            {
		            auto tmpiter = iter++;
		            auto obj = *tmpiter;
		            pool.erase(tmpiter);
	            }
                 
			}
			else
			{
				if(elephant.Health>=1)
				{
					elephant.move(Vx,Vy);
				}
				else{
					Vx =0;
					Vy =0;
					elephant.move(Vx,Vy);
				}
				elephant.update();
	           // cout<<"elephant.Health"<<elephant.Health<<endl;
				
	            
	            barrierGenerator.update();
	            enemyGenerator.update();
	            
	            if(Vx||Vy)
	            {
	            	bulletTimer.Update(50);
	            	//musicPlayer.Play("textures/running1.mp3");
				}
	            //if the delta time is greater than 0.5s,create bullets
	            if(bulletTimer.IsExpired() && elephant.Health>=1)
	            {
	                bulletTimer.Reset();
		            shared_ptr<bullet> Bullet(new bullet(elephant.getPosX()+elephant.getWidth()/2-7,elephant.getPosY()) );
		            //musicPlayer.Play("textures/laser.OGG");
	            	pool.push_back(shared_ptr<bullet>(Bullet));
				}
	
				for(auto &obj : pool)
	            {    
					obj->move(elephant.getDiffX(),elephant.getDiffY());
					obj->update();
				}
	            //Check and react for collision.
				for(auto &obj : pool)  
				{
					for(auto &another : pool)
					{
						if( obj->checkCollision(another.get()) )
	                    	obj->onCollision(another.get());
	                    if( obj->checkCollision(&elephant) )
	                    	obj->onCollision(&elephant);
					}       
	            }
	            //Offset objects to keep the elephant on the base line.
	            int objectsOffsetY = elephant.getPosY() - playerOriginY;
				resource::distance -= objectsOffsetY;
				cout<<"D : "<<resource::distance<<endl;
				for(auto &obj : pool)
	            {
	                obj->offset(0, -objectsOffsetY);
	            }
	            elephant.offset(0, -objectsOffsetY);
				//Scroll background
	            scrollingOffset += objectsOffsetY;
	            if( scrollingOffset < -resource::SCREEN_HEIGHT || scrollingOffset >resource::SCREEN_HEIGHT)
	            {
	                scrollingOffset = 0;
	            }
				resource::gBGTexture.render(0, -scrollingOffset);
				resource::gBGTexture.render(0, -scrollingOffset - resource::gBGTexture.getHeight());
			
				
				elephant.render();
	            
	           for(auto &obj : pool)
	            {
				    obj->render();
				}
				
				for(auto iter = pool.begin(); iter != pool.end();)
                {
                    auto tmpiter = iter++;
                    auto obj = *tmpiter;
 
                    if(obj->GetType()==ENTITY_TYPE_ENEMY&&obj->Health<=-1)
                    {
                        //(resource::score)++;
                        //musicPlayer.Play("../textures/Explosion.mp3");
                        cout<<"==================="<<endl;
                    }
                    if((obj->getPosX() < -resource::SCREEN_WIDTH  ||
                        obj->getPosX() > 2*resource::SCREEN_WIDTH ||
                        obj->getPosY() < -resource::SCREEN_HEIGHT ||
                        obj->getPosY() > 2*resource::SCREEN_HEIGHT||
                        obj->Health<=-1))
                    {
                        cout<<obj->GetType()<<"removed"<<endl;
                        pool.erase(tmpiter);
                    }
                }
					
				scoreText.str( "" );
				scoreText<<resource::score;
				//Render text
				SDL_Color textColor = { 0, 0, 0 };
				if( !resource::scoreTexture.loadFromRenderedText( scoreText.str().c_str(), textColor ) )
				{
					printf( "Unable to render time texture!\n" );
				}
				resource::gTextTexture.render( ( resource::SCREEN_WIDTH - resource::gTextTexture.getWidth()-70 ) , 0);
				resource::scoreTexture.render(( resource::SCREEN_WIDTH - resource::gTextTexture.getWidth()+100 ) , 0);
				
				if(elephant.Health<1) 
				{
					resource::gameoverTexture.render(180,200);
				}
			}
            
			//Update screen
			SDL_RenderPresent( resource::gRenderer );
		}
    }
    catch(exception &e)
    {
        cerr << "ERROR: " <<e.what() << endl;
    }
    catch(...)
    {
        cerr << "ERROR: Unknown error occurred!" << endl;
    }
	close();

	return 0;
}
