#ifndef BASECONTROLLER_H
#define BASECONTROLLER_H

#include <random>
#include "../Entities/Entity.h"
#include "../Field/Field.h"
#include "../Field/Cells/Wall.h"
#include "../Field/Cells/Entry.h"
#include "../Field/Cells/Exit.h"

class BaseController{
private:
    bool isAvailableToMove(unsigned int x, unsigned int y){
        if(x > field->getX() || y > field->getY())
            return false;

        if(dynamic_cast<Wall*>(field->getCell(x, y)) || dynamic_cast<Exit*>(field->getCell(x, y)) || dynamic_cast<Entry*>(field->getCell(x, y)))
            return false;

        return true;
    }

protected:
    Entity *object;
    Field *field;
    unsigned int x, y;

public:
    BaseController(Entity *object, Field *field, unsigned startPositionX, unsigned startPositionY):
                                            object(object), field(field), x(startPositionX), y(startPositionY){}

    virtual bool move(){
        if(isAvailableToMove(x, y-1)){
            field->getCell(x, y-1)->moveTo(field->getCell(x, y));
            y -= 1;
            return true;
        }

        else if(isAvailableToMove(x+1, y)){
            field->getCell(x+1, y)->moveTo(field->getCell(x, y));
            x += 1;
            return true;
        }

        else if(isAvailableToMove(x, y+1)){
            field->getCell(x, y+1)->moveTo(field->getCell(x, y));
            y += 1;
            return true;
        }

        else if(isAvailableToMove(x-1, y)){
            field->getCell(x-1, y)->moveTo(field->getCell(x, y));
            x -= 1;
            return true;
        }

        return false;
    }
};

#endif //BASECONTROLLER_H
