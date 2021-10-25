#include <iostream>
#include "Field/Field.h"
#include "Field/FieldBuilder.h"
#include "Viewers/ConsoleFieldView.h"
#include "Viewers/FieldView.h"
#include <memory>


int main(){
    /*Field f1 = FieldBuilder(5, 5, FieldBuilder::DEFAULT).build(); //init_tests
    ConsoleFieldView fv(&f1);
    std::cout << fv << std::endl;


    Field f3 = FieldBuilder(10, 10, FieldBuilder::BOX).build();
    fv.set_field(&f3);
    std::cout << fv << std::endl;*/


    /*ConsoleFieldView fv;
    Field f1 = FieldBuilder(5, 5, FieldBuilder::BOX).build(); // copy_costructor_tests
    fv.set_field(&f1);
    std::cout << fv << std::endl;

    Field f2(f1);
    fv.set_field(&f2);
    std::cout << fv << std::endl;

    Field f3 = FieldBuilder(2, 3, FieldBuilder::DEFAULT).build();
    fv.set_field(&f3);
    std::cout << fv << std::endl;

    f3 = f1;
    std::cout << fv << std::endl;
    return 0;*/


    ConsoleFieldView fv; //move_constructor_test
    Field f1 = FieldBuilder(5, 5, FieldBuilder::BOX).build();
    fv.set_field(&f1);
    std::cout << fv << std::endl;

    Field f2(std::move(f1));
    std::cout << fv << std::endl;
    fv.set_field(&f2);
    std::cout << fv << std::endl;
}