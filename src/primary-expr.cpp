#include "primary-expr.h"
#include "memory.h"
#include "helpers.h"
#include <iostream>

extern Stack *callStack;

string IdExpression::genCode() {
    string code;
    string placeStr;
    int stackOffset = callStack->getBaseOffset(id);

    place = newTemp();
    placeStr = toRegStr(place);

    if (stackOffset) {
        int siz = callStack->getSizeOfVar(id);

        if (siz == 1)
            code += lb(placeStr, stackOffset, "$fp");
        else if (siz == 4)
            code += lw(placeStr, stackOffset, "$fp");
    } else {
        DataElementType type = getDataElementType(id);
        
        code += la(placeStr, id);
    
        if (type == BYTE)
            code += lb(placeStr, 0, placeStr);
        else if (type == WORD)
            code += lw(placeStr, 0, placeStr);
    }

    return code;
}

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