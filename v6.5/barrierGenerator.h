#ifndef _BARRIER_GENERATOR_H_
#define _BARRIER_GENERATOR_H_

#include <memory>
#include <list>
#include "barrier.h"

class BarrierGenerator
{
private:
    std::list<std::shared_ptr<entity> > *pool;
    std::shared_ptr<barrier> lastBarrier;

public:
    BarrierGenerator(std::list<std::shared_ptr<entity> > *pool);

private:
    void generateBarrier();

public:
    void update();
};

#endif
