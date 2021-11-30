#ifndef CONSOLELOGGER_H
#define CONSOLELOGGER_H

#include "BaseLogger.h"
#include <iostream>


class ConsoleLogger: public BaseLogger {
protected:
    std::ostream &os;

    void createLog(Log l) override{
        os << l.getMessage() << std::endl;
    }

public:
    ConsoleLogger(std::ostream &os = std::cout): os(os){} //add some new fields and init them in constructor(format, time idk)

};


#endif //CONSOLELOGGER_H
