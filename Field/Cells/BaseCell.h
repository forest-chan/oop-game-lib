#ifndef BASECELL_H
#define BASECELL_H

#include "../../Entities/Entity.h"

class BaseCell{
protected:
    std::weak_ptr<Entity> entity;

public:
    BaseCell() = default;

    virtual BaseCell *create() = 0;

    virtual bool putEntity(std::weak_ptr<Entity> entity) = 0;

    virtual bool interact(std::weak_ptr<Entity> entity) = 0;

    virtual std::weak_ptr<Entity> getEntity() {
        return entity;
    }

    virtual ~BaseCell() = default;
};

#endif //BASECELL_H
