#ifndef OOP_GAME_PLAYER_H
#define OOP_GAME_PLAYER_H

#include "Creature.h"
#include "../../logging/BasePublisher.h"

class Player: public Creature{
public:
    Player(int hp, int dmg, int armor): Creature(hp, dmg, armor) {}

};


#endif //PLAYER_H
