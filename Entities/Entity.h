#ifndef ENTITY_H
#define ENTITY_H

#include "memory"
#include "Entities_Declarations.h"
#include <iostream>
#include "../logging/BasePublisher.h"

class Entity: public BasePublisher{
public:

    //virtual bool interact(std::shared_ptr<Entity> entity) = 0;

    virtual bool interact(Entity *entity) = 0;

    virtual bool interact(Creature &creature) = 0;

    virtual bool interact(Item &item) = 0;

    virtual ~Entity(){};

};

#endif //ENTITY_H