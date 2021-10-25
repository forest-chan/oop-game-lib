#ifndef ENTRY_H
#define ENTRY_H

#include "Cell.h"

class Entry: public Cell{
public:
    BaseCell *create() override { return new Entry; };
};

#endif //ENTRY_H
