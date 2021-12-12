#ifndef CONSOLEFIELDVIEW_H
#define CONSOLEFIELDVIEW_H

#include <iostream>
#include "../FieldView.h"
#include "CellView.h"
#include "EntityView.h"


class ConsoleFieldView : public FieldView, public CellView, public EntityView{
public:
    //using FieldView::FieldView;

    void show(std::ostream &os);

    void showInfo(std::ostream &os);

    friend std::ostream &operator<<(std::ostream &os, ConsoleFieldView &fv);


};


#endif //CONSOLEFIELDVIEW_H