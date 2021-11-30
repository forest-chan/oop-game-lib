#include "FieldBuilder.h"

Field *FieldBuilder::build() {
    Field *field = new Field(this->x, this->y);
    switch(this->type){
        case DEFAULT:
            default_generation(field);
            break;
        case BOX:
            box_generation(field);
            break;
    }
    return field;
}

void FieldBuilder::default_generation(Field *field){
    field->cells[0][0] = new Entry();
    field->cells[y-1][x-1] = new Exit();
    for(int i = 0; i < y; i++){
        for(int j = 0; j < x; j++){
            if(field->cells[i][j] == nullptr)
                field->cells[i][j] = new Cell();
        }
    }
    notify(Log::debug("default game field was created"));
}

void FieldBuilder::box_generation(Field *field){
    if(x <= 4 || y <= 4){
        notify(Log::error("was given incorrect size of box game field"));
        throw std::invalid_argument("Size of field is too small");
    }

    field->cells[1][1] = new Entry();
    field->cells[y-2][x-2] = new Exit();
    for(int i = 0; i < y; i++){
        for(int j = 0; j < x; j++){
            if(field->cells[i][j] == nullptr && (i >= 1 && j >= 1 && i < y-1 && j < x-1))
                field->cells[i][j] = new Cell();
            else if(field->cells[i][j] == nullptr)
                field->cells[i][j] = new Wall();
        }
    }
    notify(Log::debug("box game field was created"));
}

FieldBuilder &FieldBuilder::setType(FieldBuilder::Type type){
    this->type = type;
    return *this;
}

FieldBuilder &FieldBuilder::setSize(int x, int y){
    this->x = x;
    this->y = y;
    return *this;
}