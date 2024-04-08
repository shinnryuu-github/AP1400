#ifndef SUB_INGREDIENTS_H
#define SUB_INGREDIENTS_H

#include "ingredient.h"

#define DEFCLASS(classname,price)\
class classname : public Ingredient{\
public:\
    classname(size_t units) : Ingredient{price, units}{\
        this->name = #classname;\
    }\
    Ingredient* clone() override { return new classname(*this); }\
    virtual std::string get_name() override {return this->name;}\
};

DEFCLASS(Cinnamon, 5);
DEFCLASS(Chocolate, 5);
DEFCLASS(Sugar, 1);
DEFCLASS(Cookie, 10);
DEFCLASS(Espresso, 15);
DEFCLASS(Milk, 10);
DEFCLASS(MilkFoam, 5);
DEFCLASS(Water, 1);

#endif // SUB_INGREDIENTS_H