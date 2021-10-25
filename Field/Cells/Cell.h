#ifndef CELL_H
#define CELL_H

#include "BaseCell.h"

class Cell: public BaseCell{
public:
    virtual bool putEntity(std::weak_ptr<Entity> entity) override {
        if (!interact(entity.lock())){
            this->entity = entity;
            return true;
        }
        return false;
    }

    virtual bool interact(std::weak_ptr<Entity> entity) override {
        if (this->entity.lock()) {
            entity.lock()->interact(this->entity.lock());
            this->entity.lock()->interact(entity.lock());
            return true;
        }
        return false;
    }

    BaseCell *create() override { return new Cell; };
};

#endif //CELL_H
