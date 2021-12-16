#ifndef FIELD_H
#define FIELD_H

#include <iostream>
#include <utility>
#include <memory>
#include "Cells/BaseCell.h"
#include "../logging/BasePublisher.h"
#include "../logging/loggers/BaseLogger.h"

#define MAX_FIELD_HEIGHT 50
#define MAX_FIELD_WIDTH 50
#define MIN_FIELD_HEIGHT 4
#define MIN_FIELD_WIDTH 4

class Field: public BasePublisher {
    friend class FieldBuilder;

    friend class FieldView;

    friend class ConsoleFieldView;

private:
    unsigned int x, y;
    BaseCell ***cells;

protected:
    Field(unsigned int x, unsigned int y);


public:
    Field(const Field &other);

    Field &operator=(const Field &other);

    Field(Field &&other);

    Field &operator=(Field &&other);

    BaseCell *getCell(int x, int y);

    int getX();

    int getY();

    void addNewLogger(std::shared_ptr<BaseLogger> logger) override;

    void deleteLogger(std::shared_ptr<BaseLogger> logger) override;

    virtual ~Field();
};

#endif //FIELD_H
