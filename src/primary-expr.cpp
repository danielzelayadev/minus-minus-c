#include "primary-expr.h"
#include "memory.h"
#include "helpers.h"
#include <iostream>

extern Stack *callStack;

string IdExpression::genAddrCode() {
    string placeStr;
    int stackOffset = callStack->getBaseOffset(id);

    place = newTemp();
    placeStr = toRegStr(place);
    
    return stackOffset ?
        addi(placeStr, "$fp", stackOffset) :
        la(placeStr, id);
}

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