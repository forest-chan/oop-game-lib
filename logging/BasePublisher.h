#ifndef BASEPUBLISHER_H
#define BASEPUBLISHER_H

#include <list>
#include <memory>
#include "loggers/BaseLogger.h"
#include <iostream>

class BasePublisher {
protected:
    std::list<std::shared_ptr<BaseLogger>> loggers;

protected:
    virtual void notify(Log l){
        for(auto &logger : loggers){
            (*logger) << l;
        }
    }

public:
    virtual void addNewLogger(std::shared_ptr<BaseLogger> logger){
        loggers.push_back(logger);
    }

    virtual void deleteLogger(std::shared_ptr<BaseLogger> logger){
        for(auto iter = loggers.begin(); iter != loggers.end(); iter++){
            if(logger.get() == iter->get()){
                loggers.erase(iter);
                break;
            }
        }
    }

};

#endif //BASEPUBLISHER_H
