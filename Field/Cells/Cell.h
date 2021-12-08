#ifndef CELL_H
#define CELL_H

#include "BaseCell.h"

class Cell: public BaseCell{
public:
    bool putEntity(Entity *entity) override {
        if(!this->entity){
            this->entity = entity;
            notify(Log::debug("an entity was moved to an empty cell"));
            return true;
        }

        if(dynamic_cast<Item*>(entity)){// предмет не может ходить
            notify(Log::warn("An item can't interact with other Entities"));
            return false;
        }

        if(entity->interact(this->entity)){
            Creature *c = dynamic_cast<Creature*>(entity);
            Item *i = dynamic_cast<Item*>(this->entity);
            if(c && c->getHp() <= 0){ // ходящий помер:(
                notify(Log::debug("moving creature was destroyed"));
                return false;
            }

            if(i){ // заюзали шмотку на клетке, на которую был совершен ход
                this->entity = entity;
                notify(Log::debug("an item on cell was used"));
                return true;
            }
        }

        if(this->entity->interact(entity)){
            Creature *c = dynamic_cast<Creature*>(this->entity);
            if(c && c->getHp() <= 0){
                this->entity = entity;
                notify(Log::debug("creature on cell was destroyed"));
                return true;
            }

        }

        return false;
    }

    BaseCell *create() override { return new Cell; };
};

#endif //CELL_H
