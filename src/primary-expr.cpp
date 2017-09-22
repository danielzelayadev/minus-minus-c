#include "primary-expr.h"
#include "memory.h"
#include "helpers.h"
#include <iostream>

string StringExpression::genCode() {
    place = newTemp();

    return la(toRegStr(place), newString(*literal));
}

string IntExpression::genCode() {
    place = newTemp();
    
    return "li " + toRegStr(place) + ", " + *literal + "\n";
}

string CharExpression::genCode() {
    place = newTemp();
    
    return "li " + toRegStr(place) + ", " + *literal + "\n";
}