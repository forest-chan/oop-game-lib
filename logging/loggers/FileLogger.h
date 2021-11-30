#ifndef FILELOGGER_H
#define FILELOGGER_H

#include "BaseLogger.h"
#include <fstream>
#include <iostream>

class FileLogger: public BaseLogger {
protected:
    std::ofstream f;

    void createLog(Log l){
        f << l.getMessage() << std::endl;
    }

public:
    FileLogger(std::string fileName="log.txt"){
        f.open(fileName);
    }

    virtual ~FileLogger() override{
        f.close();
    }
};

#endif //FILELOGGER_H
