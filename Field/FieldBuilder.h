#ifndef FIELDBUILDER_H
#define FIELDBUILDER_H

#include "Field.h"
#include "Cells/Cell.h"
#include "Cells/Entry.h"
#include "Cells/Exit.h"
#include "Cells/Wall.h"

class FieldBuilder{
public:
    enum Type{
        DEFAULT,
        BOX
    };

protected:
    unsigned int x, y;
    Type type;

    Field default_generation();

    Field box_generation();

public:
    FieldBuilder() = delete;

    FieldBuilder(unsigned int x, unsigned int y, Type type);

    Field build();

    ~FieldBuilder() = default;

};

#endif //FIELDBUILDER_H
