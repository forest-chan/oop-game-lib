#ifndef FIELD_H
#define FIELD_H

#include <iostream>
#include <utility>
#include <memory>
#include "Cells/BaseCell.h"
#include "../logging/BasePublisher.h"
#include "../logging/loggers/BaseLogger.h"

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

    void addNewLogger(std::shared_ptr<BaseLogger> logger) override;

    void deleteLogger(std::shared_ptr<BaseLogger> logger) override;



    virtual ~Field();
};

#endif //FIELD_H
