#ifndef FIELDBUILDER_H
#define FIELDBUILDER_H

#include "Field.h"
#include "Cells/Cell.h"
#include "Cells/Entry.h"
#include "Cells/Exit.h"
#include "Cells/Wall.h"
#include "../logging/BasePublisher.h"

class FieldBuilder: public BasePublisher{
public:
    enum Type{
        DEFAULT,
        BOX
    };

protected:
    unsigned int x, y;
    Type type;

    void default_generation(Field *f);

    void box_generation(Field *f);

public:
    FieldBuilder() = default;

    FieldBuilder &setType(Type type);

    FieldBuilder &setSize(int x, int y);

    Field *build();

    ~FieldBuilder() = default;

};

#endif //FIELDBUILDER_H
