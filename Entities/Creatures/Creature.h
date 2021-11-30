#ifndef CREATURE_H
#define CREATURE_H

#include "../Entity.h"
#include "../../logging/Log.h"

class Creature: public Entity{
protected:
    int hp, dmg, armor;

    bool interact(Creature &creature) override{
        int new_armor = creature.getArmor() - this->getDmg();
        int new_hp = creature.getHp();

        if(new_armor < 0){
            new_hp += new_armor;
            new_armor = 0;
        }

        creature.setArmor(new_armor);
        creature.setHp(new_hp);
        notify(Log::debug("creature interacted with creature"));
        //notify(*this, "creature interacted with creature");
        return true;
    }

    bool interact(Item &item) override{
        notify(Log::warn("item can't interact with creature"));
        //notify(*this, "item can't interact with creature");
        return false;
    }

public:
    Creature(int hp, int dmg, int armor): hp(hp), dmg(dmg), armor(armor) {}

    bool interact(Entity *entity) override {
        return entity->interact(*this);
    }

    int getHp(){
        return this->hp;
    }

    int getDmg() {
        return this->dmg;
    }

    int getArmor() {
        return this->armor;
    }

    void setHp(int hp) {
        this->hp = hp;
    }

    void setDmg(int dmg){
        this->dmg = dmg;
    }

    void setArmor(int armor){
        this->armor = armor;
    }

    virtual ~Creature() = default;

};
#endif //CREATURE_H
