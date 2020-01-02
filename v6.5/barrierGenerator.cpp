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

    lastBarrier = shared_ptr<barrier>(new barrier(x, y));
    pool->push_back(lastBarrier);
}

void BarrierGenerator::update()
{
    // Generate new barrier only if
    // there is a good safe distance from the last barrier.
    if( !lastBarrier || lastBarrier->getPosY() >= 0 )
        generateBarrier();
}
