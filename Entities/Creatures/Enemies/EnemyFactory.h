#ifndef ENEMYFACTORY_H
#define ENEMYFACTORY_H

#include "../Creature.h"
#include "Enemy.h"

class EnemyFactory {
public:
    virtual Creature *create() = 0;
};

class LightEnemyFactory: public EnemyFactory {
    Creature *create() override {
        return new Enemy(10, 2, 0);
    }
};

class MediumEnemyFactory: public EnemyFactory {
    Creature *create() override {
        return new Enemy(15, 3, 5);
    }
};

class HeavyEnemyFactory: public EnemyFactory {
    Creature *create() override {
        return new Enemy(15, 4, 10);
    }
};

#endif //ENEMYFACTORY_H
