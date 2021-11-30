#ifndef ENTITYVIEW_H
#define ENTITYVIEW_H

#include <map>
#include "ConsoleObjectView.h"
#include "../../Entities/Entity.h"
#include "../../Entities/Creatures/Creature.h"
#include "../../Entities/Creatures/Player.h"
#include "../../Entities/Creatures/Enemies/Enemy.h"
#include "../../Entities/Items/Item.h"

class EntityView : ConsoleObjectView<Entity> {
public:
    EntityView();

    char getChar(const Entity &c);
};


#endif //ENTITYVIEW_H
