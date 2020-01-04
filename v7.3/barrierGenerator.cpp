#include "resource.h"
#include "barrierGenerator.h"

using namespace std;

BarrierGenerator::BarrierGenerator(list<shared_ptr<entity> > *pool)
    : pool(pool)
{
}

void BarrierGenerator::generateBarrier()
{
    int y = - resource::BARRIER_Y_DISTANCE;
    int x = rand() % ( resource::SCREEN_WIDTH - resource::BARRIER_WIDTH );

    newBarrier = new barrier(x, y);
    pool->push_back(shared_ptr<barrier>(newBarrier));
}

void BarrierGenerator::update()
{
    // Generate new barrier only if
    // there is a good safe distance from the last barrier.
    if( resource::distance>300) {
    	//cout<<"distance : "<<resource::distance<<endl;
	    generateBarrier();
	    resource::distance =1;
    }
}
