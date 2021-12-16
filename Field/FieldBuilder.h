#ifndef FIELDBUILDER_H
#define FIELDBUILDER_H

#include <random>
#include "Field.h"
#include "Cells/Cell.h"
#include "Cells/Entry.h"
#include "Cells/Exit.h"
#include "Cells/Wall.h"
#include "../logging/BasePublisher.h"
#include "../saving/CellInfo.h"
#include "../saving/FieldInfo.h"


class FieldBuilder: public BasePublisher{
public:
    enum Type{
        DEFAULT,
        BOX,
        RANDOM
    };

protected:
    unsigned int x, y;
    Type type;

    void default_generation(Field *f);

    void box_generation(Field *f);

    void add_random_walls(Field *f);

public:
    FieldBuilder() = default;

    FieldBuilder &setType(Type type);

    FieldBuilder &setSize(int x, int y);

    Field *build();

    Field *createFromInfo(CellInfo ***cellsInfo, FieldInfo *fieldInfo);

    ~FieldBuilder() = default;

};

#endif //FIELDBUILDER_H
