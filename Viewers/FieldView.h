#ifndef FIELDVIEW_H
#define FIELDVIEW_H

#include "../Field/Field.h"


class FieldView{
protected:
    Field *field = nullptr;
public:
    FieldView() = default;

    FieldView(Field *field): field(field) {};

    void set_field(Field *field){
        this->field = field;
    }

    virtual ~FieldView() = default;

};


#endif //FIELDVIEW_H
