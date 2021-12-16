#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <iostream>
#include <utility>
#include "BaseController.h"


class PlayerController: public BaseController{
protected:
    bool isAvailableToMove(unsigned int x, unsigned int y) override{
        if(x > field->getX() || y > field->getY())
            return false;

        if(dynamic_cast<Wall*>(field->getCell(x, y)))
            return false;

        return true;
    }

public:
    PlayerController(Entity *object, Field *field, unsigned startPositionX, unsigned startPositionY):
        BaseController(object, field, startPositionX, startPositionY){}

    std::string move() override{
        int c = getchar();

        if(c != '\n'){

            if(c == keys["KEY_UP"]){
                if(isAvailableToMove(x, y-1)){
                    AbsMove(x, y-1);
                    y -= 1;
                    return "success";
                }
            }
            else if(c == keys["KEY_DOWN"]){
                if(isAvailableToMove(x, y+1)){
                    AbsMove(x, y+1);
                    y += 1;
                    return "success";
                }
            }
            else if(c == keys["KEY_RIGHT"]){
                if(isAvailableToMove(x+1, y)){
                    AbsMove(x+1, y);
                    x += 1;
                    return "success";
                }
            }
            else if(c == keys["KEY_LEFT"]){
                if(isAvailableToMove(x-1, y)){
                    AbsMove(x-1, y);
                    x -= 1;
                    return "success";
                }
            }
            else if(c == keys["KEY_SAVE"]){
                return "save";
            }
            else if(c == keys["KEY_LOAD"]){

                return "load";

            }
            else{
                return "fail";
            }
        }
        return "fail";
    }
};


#endif //PLAYERCONTROLLER_H
