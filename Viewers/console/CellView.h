#ifndef CELLVIEW_H
#define CELLVIEW_H

#include "../../Field/Cells/Cell.h"
#include "../../Field/Cells/Wall.h"
#include "../../Field/Cells/Entry.h"
#include "../../Field/Cells/Exit.h"
#include "ConsoleObjectView.h"
#include <map>

class CellView: ConsoleObjectView<BaseCell>{
public:
    CellView();

    char getChar(const BaseCell &c);
};


#endif //CELLVIEW_H
