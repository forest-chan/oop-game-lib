#ifndef ENTITY_H
#define ENTITY_H

#include "memory"

class Entity {
public:
    virtual bool interact(std::shared_ptr<Entity> entity) = 0;
};

#endif //ENTITY_H