#include "resource.h"
#include "enemyGenerator.h"

using namespace std;

EnemyGenerator::EnemyGenerator(list<shared_ptr<entity> > *pool)
    : pool(pool)
{
}

void EnemyGenerator::generateEnemy()
{
    for(int i=0;i<2;i++)
	{
    	lastEnemy = shared_ptr<Enemy>(new Enemy(rand()));
    	pool->push_back(lastEnemy);
	}
    
}

void EnemyGenerator::update()
{
	static int count=0;
	count++; 
   if( count>300)
   {
   	count=0;
   	generateEnemy();
   }
    	
	
        
}
