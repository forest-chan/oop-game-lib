#ifndef OOP_GAME_ITEMFACTORY_H
#define OOP_GAME_ITEMFACTORY_H

#include "Item.h"


class ItemFactory {
public:
    virtual Item *create(int value) = 0;
};

class HealFactory: public ItemFactory {
public:
    Item *create(int value) override {
        return new HealItem(value);
    }
};

class DmgFactory: public ItemFactory {
public:
    Item *create(int value) override {
        return new DmgItem(value);
    }
};

class ArmorFactory: public ItemFactory {
public:
    Item *create(int value) override {
        return new ArmorItem(value);
    }
};

#endif //ITEMFACTORY_H
