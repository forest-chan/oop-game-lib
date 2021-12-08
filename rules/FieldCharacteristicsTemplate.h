#ifndef FIELDCHARACTERISTICSTEMPLATE_H
#define FIELDCHARACTERISTICSTEMPLATE_H

template<typename T>
class FieldCharacteristicsTemplate{
public:
    FieldCharacteristicsTemplate(T x, T y, FieldBuilder::Type fieldType): x(x), y(y), fieldType(fieldType){
        static_assert(std::is_same<T, int>::value, "template instantiation of Class are not int");
    }

    T getX(){
        return x;
    }

    T getY(){
        return y;
    }

    FieldBuilder::Type getFieldType(){
        return fieldType;
    }

private:
    T x, y;
    FieldBuilder::Type fieldType;
};


#endif //FIELDCHARACTERISTICSTEMPLATE_H
