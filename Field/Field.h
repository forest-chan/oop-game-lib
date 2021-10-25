#ifndef FIELD_H
#define FIELD_H

#include <iostream>
#include <utility>
#include "Cells/BaseCell.h"

class Field {
    friend class FieldBuilder;
    friend class FieldView;
    friend class ConsoleFieldView;

private:
    unsigned int x, y;
    BaseCell ***cells;

protected:
    Field(unsigned int x, unsigned int y);

public:
    Field(const Field &other);

    Field &operator=(const Field &other);

    Field(Field &&other);

    Field &operator=(Field &&other);

    virtual ~Field();
};

#endif //FIELD_H
