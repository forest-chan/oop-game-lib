#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <iostream>
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

    bool move() override{
        int c = getchar();

        if(c != '\n'){

            if(c == keys["KEY_UP"]){
                if(isAvailableToMove(x, y-1)){
                    AbsMove(x, y-1);
                    y -= 1;
                    return true;
                }
            }
            else if(c == keys["KEY_DOWN"]){
                if(isAvailableToMove(x, y+1)){
                    AbsMove(x, y+1);
                    y += 1;
                    return true;
                }
            }
            else if(c == keys["KEY_RIGHT"]){
                if(isAvailableToMove(x+1, y)){
                    AbsMove(x+1, y);
                    x += 1;
                    return true;
                }
            }
            else if(c == keys["KEY_LEFT"]){
                if(isAvailableToMove(x-1, y)){
                    AbsMove(x-1, y);
                    x -= 1;
                    return true;
                }
            }
            else{
                return false;
            }

            /*switch(c){
                case UP:
                    if(isAvailableToMove(x, y-1)){
                        AbsMove(x, y-1);
                        y -= 1;
                        return true;
                    }
                    break;
                case RIGHT:
                    if(isAvailableToMove(x+1, y)){
                        AbsMove(x+1, y);
                        x += 1;
                        return true;
                    }
                    break;
                case DOWN:
                    if(isAvailableToMove(x, y+1)){
                        AbsMove(x, y+1);
                        y += 1;
                        return true;
                    }
                    break;
                case LEFT:
                    if(isAvailableToMove(x-1, y)){
                        AbsMove(x-1, y);
                        x -= 1;
                        return true;
                    }
                    break;
                default:
                    return false;
            }*/
        }

        return false;
    }
};


#endif //PLAYERCONTROLLER_H
