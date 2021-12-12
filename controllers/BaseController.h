#ifndef BASECONTROLLER_H
#define BASECONTROLLER_H

#include <random>
#include <map>
#include <string>
#include <fstream>
#include <vector>
#include "../Entities/Entity.h"
#include "../Field/Field.h"
#include "../Field/Cells/Wall.h"
#include "../Field/Cells/Entry.h"
#include "../Field/Cells/Exit.h"

class BaseController{
protected:
    Entity *object;
    Field *field;
    unsigned int x, y;
    int keysCount;
    std::map<std::string, int> keys;
    std::vector<int> keyChars;
    std::string keysLocation = "controllers/keys.txt";

    virtual bool isAvailableToMove(unsigned int x, unsigned int y){
        if(x > field->getX() || y > field->getY())
            return false;

        if(dynamic_cast<Wall*>(field->getCell(x, y)) || dynamic_cast<Exit*>(field->getCell(x, y)) || dynamic_cast<Entry*>(field->getCell(x, y)))
            return false;

        return true;
    }

    virtual void AbsMove(int x_new, int y_new){
        field->getCell(x_new, y_new)->moveTo(field->getCell(x, y));
    }

    virtual bool checkForPlayerMovement(){
        if(dynamic_cast<Player*>(field->getCell(x, y)->getEntity()))
            return true;
        return false;
    }

    bool readKeys(){
        std::ifstream f(keysLocation);
        if(f.is_open()){
            std::string str;

            for(int i = 0; i < keysCount; i++) {
                getline(f, str);
                keyChars.push_back(str[0]); //std::stoi(str)
            }

            if(keyChars.size() != keysCount){
                f.close();
                return false;
            }

            keys = {
                    {"KEY_UP", keyChars[0]},
                    {"KEY_DOWN", keyChars[1]},
                    {"KEY_RIGHT", keyChars[2]},
                    {"KEY_LEFT", keyChars[3]}
            };

            f.close();
            return true;
        }
        return false;
    }

    bool writeKeys(){
        if(!keys.empty()){
            FILE *f = std::fopen(keysLocation.c_str(), "w");

            for(std::vector<int>::size_type i=0;i!=keyChars.size();i++){
                fprintf(f, "%c\n", keyChars[i]);
            }

            std::fclose(f);
            return true;
        }
        return false;
    }

    void setDefaultKeys(){
        keys = {
                {"KEY_UP", 'w'},
                {"KEY_DOWN", 's'},
                {"KEY_RIGHT", 'd'},
                {"KEY_LEFT", 'a'}
        };
        keyChars.push_back('w');
        keyChars.push_back('s');
        keyChars.push_back('d');
        keyChars.push_back('a');
        writeKeys();
    }

public:
    BaseController(Entity *object, Field *field, unsigned startPositionX, unsigned startPositionY):
                                            object(object), field(field), x(startPositionX), y(startPositionY){
        keysCount = 4;
        if(!readKeys())
            setDefaultKeys();
    }

    virtual bool move(){
        if(checkForPlayerMovement())
            return false;

        if(isAvailableToMove(x, y-1)){
            AbsMove(x, y-1);
            y -= 1;
            return true;
        }

        else if(isAvailableToMove(x+1, y)){
            AbsMove(x+1, y);
            x += 1;
            return true;
        }

        else if(isAvailableToMove(x, y+1)){
            AbsMove(x, y+1);
            y += 1;
            return true;
        }

        else if(isAvailableToMove(x-1, y)){
            AbsMove(x-1, y);
            x -= 1;
            return true;
        }

        return false;
    }

    int getX(){
        return x;
    }

    int getY(){
        return y;
    }
};

#endif //BASECONTROLLER_H
