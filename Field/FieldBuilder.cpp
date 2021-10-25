#include "FieldBuilder.h"

FieldBuilder::FieldBuilder(const unsigned int x, const unsigned int y, Type type): x(x), y(y), type(type){}

Field FieldBuilder::build() {
    switch(type){
        case DEFAULT:
            return default_generation();
        case BOX:
            return box_generation();
        default:
            return default_generation();
    }
}

Field FieldBuilder::default_generation(){
    Field field(x, y);
    field.cells[0][0] = new Entry();
    field.cells[y-1][x-1] = new Exit();
    for(int i = 0; i < y; i++){
        for(int j = 0; j < x; j++){
            if(field.cells[i][j] == nullptr)
                field.cells[i][j] = new Cell();
        }
    }
    return Field(std::move(field));
}

Field FieldBuilder::box_generation(){
    if(x <= 4 || y <= 4)
        throw std::invalid_argument("Size of field is too small");

    Field field(x, y);
    field.cells[1][1] = new Entry();
    field.cells[y-2][x-2] = new Exit();
    for(int i = 0; i < y; i++){
        for(int j = 0; j < x; j++){
            if(field.cells[i][j] == nullptr && (i >= 1 && j >= 1 && i < y-1 && j < x-1))
                field.cells[i][j] = new Cell();
            else if(field.cells[i][j] == nullptr)
                field.cells[i][j] = new Wall();
        }
    }
    return Field(std::move(field));
}