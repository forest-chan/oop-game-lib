#ifndef LOG_H
#define LOG_H


#include <string>


class Log {
protected:
    std::string message;

public:
    enum LogLevel{
        OFF,
        ERROR,
        WARN,
        DEBUG,
        INFO,
        ALL,
    }level;

    Log(Log::LogLevel lvl, std::string msg): level(lvl), message(msg){
        if(level <= OFF || level >= ALL)
            throw std::invalid_argument("incorrect log level");
    }

    virtual std::string getMessage(){
        return message;
    }

    static Log debug(std::string msg){
        return Log(Log::LogLevel::DEBUG, msg);
    }

    static Log error(std::string msg){
        return Log(Log::LogLevel::ERROR, msg);
    }

    static Log warn(std::string msg){
        return Log(Log::LogLevel::WARN, msg);
    }

    static Log info(std::string msg){
        return Log(Log::LogLevel::INFO, msg);
    }

};

#endif //LOG_H
