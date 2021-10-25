#ifndef EXIT_H
#define EXIT_H

#include "Cell.h"

class Exit: public Cell{
public:
    BaseCell *create() override { return new Exit; };
};

#endif //EXIT_H
