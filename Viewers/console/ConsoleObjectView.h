#ifndef CONSOLEOBJECTVIEW_H
#define CONSOLEOBJECTVIEW_H

#include <map>
#include <vector>


template <class T>
class ConsoleObjectView{
protected:
    std::map<size_t, char> chars;

public:
    ConsoleObjectView(std::map<size_t, char> chars): chars(chars){};

    virtual char getChar(const T &c){
        return '\0';
    }
};

#endif //CONSOLEOBJECTVIEW_H
