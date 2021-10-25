#ifndef CONSOLEFIELDVIEW_H
#define CONSOLEFIELDVIEW_H

#include "FieldView.h"
#include "CellView.h"
#include <iostream>

class ConsoleFieldView : public FieldView {
public:
    using FieldView::FieldView;

    void show(std::ostream &os) const;

    friend std::ostream &operator<<(std::ostream &os, ConsoleFieldView &fv);
};

#endif //CONSOLEFIELDVIEW_H
