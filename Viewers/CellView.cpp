#include "CellView.h"


const char CellView::CELLS_CHARS[] = {'O', '#', '@', '$'};

const std::map<size_t, char>CellView::chars = {
        {typeid(Cell).hash_code(),     CELLS_CHARS[0]},
        {typeid(Wall).hash_code(),     CELLS_CHARS[1]},
        {typeid(Entry).hash_code(), CELLS_CHARS[2]},
        {typeid(Exit).hash_code(),     CELLS_CHARS[3]}
};

char CellView::get_char(BaseCell *p) {
    return chars.at(typeid(*p).hash_code());
}

char CellView::get_char(const BaseCell& c) {
    return chars.at(typeid(c).hash_code());
}