#ifndef ENEMY_H
#define ENEMY_H

#include "../Creature.h"

class Enemy: public Creature{
public:
    Enemy(int hp, int dmg, int armor): Creature(hp, dmg, armor) {}
};

#endif //ENEMY_H
