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
        case RANDOM:
            box_generation(field);
            add_random_walls(field);
            break;
        default:
            notify(Log::error("invalid type of field was given"));
            throw std::invalid_argument("unknown type of field");
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

void FieldBuilder::add_random_walls(Field *field){
    int count_walls = static_cast<int>((x+y) / 3 + 1);

    while(count_walls){
        std::random_device rd;
        std::mt19937 mersenne(rd());

        int x_wall = mersenne() % (x-4) + 2,
                y_wall = mersenne() % (y-4) + 2;

        if(!(dynamic_cast<Wall*>(field->cells[y_wall][x_wall])) && !(dynamic_cast<Entry*>(field->cells[y_wall][x_wall]))
                && !(dynamic_cast<Exit*>(field->cells[y_wall][x_wall]))){

            delete field->cells[y_wall][x_wall];
            field->cells[y_wall][x_wall] = new Wall();
            count_walls--;

        }
    }

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