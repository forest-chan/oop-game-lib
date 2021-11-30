#ifndef ITEM_H
#define ITEM_H

#include "../Entity.h"
#include "../Creatures/Creature.h"
#include "../../logging/Log.h"

class Item: public Entity{
protected:
    int value = 0;

    bool interact(Creature &creature) override {
        action(creature);
        notify(Log::debug("creature interacted with item"));
        //notify(*this, "creature interacted with item");
        return true;
    }

    bool interact(Item &item) override {
        notify(Log::warn("item can't interact with item"));
        //notify(*this, "item can't interact with item");
        return false;
    }

    virtual bool action(Creature &creature) = 0;


public:

    bool interact(Entity *entity) override { //переписать на обратное
        return entity->interact(*this);
    }

    Item(int value): value(value){}

};


class HealItem: public Item {
public:
    HealItem(int value): Item(value){}

    bool action(Creature &creature) override {
        int new_hp = creature.getHp() + this->value;
        creature.setHp(new_hp);
        return true;
    }

};

class DmgItem: public Item {
public:
    DmgItem(int value): Item(value){}

    bool action(Creature &creature) override {
        int new_dmg = creature.getDmg() + this->value;
        creature.setDmg(new_dmg);
        return true;
    }

};

class ArmorItem: public Item {
public:
    ArmorItem(int value): Item(value){}

    bool action(Creature &creature) override {
        int new_armor = creature.getArmor() + this->value;
        creature.setArmor(new_armor);
        return true;
    }

};

#endif //ITEM_H
