#ifndef BASELOGGER_H
#define BASELOGGER_H

#include "../Log.h"

class BaseLogger {
protected:

    virtual void createLog(Log l) = 0;

public:

     BaseLogger() = default;


     BaseLogger &operator<<(Log l){
         createLog(l);
         return *this;
     }

     virtual ~BaseLogger() = default;


};


#endif //BASELOGGER_H
