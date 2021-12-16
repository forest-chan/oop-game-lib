#ifndef FIELDINFO_H
#define FIELDINFO_H

#include "../Field/Field.h"
#include "../Field/FieldBuilder.h"

class FieldInfo{
public:
    int x, y;

    FieldInfo(){}

    FieldInfo(int x, int y){
        this->x = x;
        this->y = y;
    }

};

#endif //FIELDINFO_H
