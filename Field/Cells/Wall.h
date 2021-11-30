#ifndef WALL_H
#define WALL_H

#include "BaseCell.h"

class Wall: public BaseCell{
public:
    bool putEntity(Entity *entity) override{
        return false;
    }

    BaseCell *create() override { return new Wall; };
};

#endif //WALL_H
