#ifndef _ENEMY_GENERATOR_H_
#define _ENEMY_GENERATOR_H_

#include <memory>
#include <list>
#include "enemy.h"
class EnemyGenerator
{
private:
    std::list<std::shared_ptr<entity> > *pool;
    std::shared_ptr<Enemy> lastEnemy;
    

public:
    EnemyGenerator(std::list<std::shared_ptr<entity> > *pool);
private:
    void generateEnemy();

public:
    void update();
};
#endif

