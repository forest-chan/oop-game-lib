#include "Field.h"


Field::Field(unsigned int x, unsigned int y): x(x), y(y){
    cells = new BaseCell **[this->y];
    for(int i = 0; i < this->y; i++){
        cells[i] = new BaseCell *[this->x];
        for(int j = 0; j < this->x; j++)
            cells[i][j] = nullptr;
    }
}

Field::~Field(){
    for(int i = 0; i < y; i++){
        for(int j = 0; j < x; j++){
            if(cells[i][j]->getEntity())
                delete cells[i][j]->getEntity();
            delete cells[i][j];
        }
        delete[] cells[i];
    }
    delete[] cells;
}

Field::Field(const Field &other){
    x = other.x;
    y = other.y;
    cells = new BaseCell **[y];
    for(int i = 0; i < y; i++){
        cells[i] = new BaseCell *[x];
        for(int j = 0; j < x; j++)
            cells[i][j] = other.cells[i][j]->create();
    }
}

Field &Field::operator=(const Field &other){
    if(this != &other){
        for(int i = 0; i < y; i++){
            for(int j = 0; j < x; j++)
                delete cells[i][j];
            delete[] cells[i];
        }
        delete[] cells;

        x = other.x;
        y = other.y;
        cells = new BaseCell **[y];
        for(int i = 0; i < y; i++){
            cells[i] = new BaseCell *[x];
            for(int j = 0; j < x; j++)
                cells[i][j] = other.cells[i][j]->create();
        }
    }
    return *this;
}

Field::Field(Field &&other){
    x = std::exchange(other.x, 0);
    y = std::exchange(other.y, 0);
    cells = std::exchange(other.cells, nullptr);
}

Field &Field::operator=(Field &&other){
    if(this != &other){
        for(int i = 0;i < y; i++){
            for(int j = 0; j < x; j++)
                delete cells[i][j];
            delete[] cells[i];
        }
        delete[] cells;

        x = std::exchange(other.x, 0);
        y = std::exchange(other.y, 0);
        cells = std::exchange(other.cells, nullptr);
    }
    return *this;
}


void Field::addNewLogger(std::shared_ptr<BaseLogger> logger){
    for(int i = 0; i < this->y; i++){
        for(int j = 0; j < this->x; j++){
            this->cells[i][j]->addNewLogger(logger);
        }
    }
}

void Field::deleteLogger(std::shared_ptr<BaseLogger> logger){
    for(int i = 0; i < this->y; i++){
        for(int j = 0; j < this->x; j++){
            this->cells[i][j]->deleteLogger(logger);
        }
    }
}


BaseCell *Field::getCell(int x, int y){
    return this->cells[y][x];
}

int Field::getX(){
    return x;
}

int Field::getY(){
    return y;
}