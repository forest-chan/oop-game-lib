#ifndef BASECELL_H
#define BASECELL_H

#include "../../Entities/Entity.h"
#include "../../Entities/Creatures/Creature.h"
#include "../../Entities/Items/Item.h"
#include "../../Entities/Creatures/Player.h"
#include "../../Entities/Creatures/Enemies/Enemy.h"
#include "../../logging/BasePublisher.h"



class BaseCell: public BasePublisher{
protected:
    Entity *entity = nullptr;
public:

    BaseCell() = default;

    virtual BaseCell *create() = 0;

    virtual bool putEntity(Entity *entity) = 0;

    virtual bool moveTo(BaseCell *cell){
        if(this != cell &&  cell->getEntity() != nullptr && putEntity(cell->getEntity())){ //entity != nullptr
            cell->entity = nullptr;
            notify(Log::debug("the object located on the cell from which the move was made has been moved to a new cell"));
            return true;
        }
        notify(Log::debug("the move to a new cell wasn't made"));
        return false;
    }

    virtual Entity *getEntity(){
        return entity;
    }

    virtual bool isPlayer(){
        if(dynamic_cast<Player*>(this->entity)){
            return true;
        }
        return false;
    }

    virtual bool isEnemy(){
        if(dynamic_cast<Enemy*>(this->entity)){
            return true;
        }
        return false;
    }

    virtual bool isHealItem(){
        if(dynamic_cast<HealItem*>(this->entity)){
            return true;
        }
        return false;
    }

    virtual bool isDmgItem(){
        if(dynamic_cast<DmgItem*>(this->entity)){
            return true;
        }
        return false;
    }

    virtual bool isArmorItem(){
        if(dynamic_cast<ArmorItem*>(this->entity)){
            return true;
        }
        return false;
    }


    virtual ~BaseCell() = default;

};

#endif //BASECELL_H
