#include "primary-expr.h"
#include "memory.h"
#include <iostream>

string StringExpression::genCode() {
    place = newTemp();

    return "la $t" + to_string(place) + ", " + newString(*literal) + "\n";
}

string IntExpression::genCode() {
    return "";
}

string CharExpression::genCode() {
    return "";
}