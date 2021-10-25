#ifndef OOP_GAME_CELLVIEW_H
#define OOP_GAME_CELLVIEW_H

#include "../Field/Cells/Cell.h"
#include "../Field/Cells/Wall.h"
#include "../Field/Cells/Entry.h"
#include "../Field/Cells/Exit.h"
#include <map>

class CellView{
    static const char CELLS_CHARS[];
    static const std::map<size_t, char> chars;
public:
    static char get_char(BaseCell *p);

    static char get_char(const BaseCell &ref);
};


#endif //CELLVIEW_H
