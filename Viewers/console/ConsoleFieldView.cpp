#include "ConsoleFieldView.h"

void ConsoleFieldView::show(std::ostream &os) {
    if (field != nullptr) {
        if (field->cells != nullptr) {
            for (int i = 0; i < field->y; ++i) {
                for (int j = 0; j < field->x; ++j) {
                    if (field->getCell(j, i)->getEntity()){
                        os << EntityView::getChar(*field->getCell(j, i)->getEntity()) << " ";
                    }
                    else{
                        os << CellView::getChar(*field->getCell(j, i)) << " ";
                    }
                }
                os << '\n';
            }
        }
    }
}


std::ostream &operator<<(std::ostream &os, ConsoleFieldView &fv) {
    fv.show(os);
    return os;
}

void ConsoleFieldView::showInfo(std::ostream &os) {
    if (!field)
        os << "size:" << field->x << "x" << field->y << " cells: " << field->cells << '\n';
}

