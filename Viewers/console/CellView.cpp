#include "CellView.h"

CellView::CellView() : ConsoleObjectView<BaseCell>(
        {
                {typeid(Cell).hash_code(),     '.'},
                {typeid(Wall).hash_code(),     '#'},
                {typeid(Entry).hash_code(), '@'},
                {typeid(Exit).hash_code(),     '$'}
        }
) {}

char CellView::getChar(const BaseCell &c) {
    return chars.at(typeid(c).hash_code());
}