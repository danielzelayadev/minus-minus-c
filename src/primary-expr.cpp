#include "primary-expr.h"
#include "memory.h"
#include "helpers.h"
#include <iostream>

extern Stack *callStack;

string IdExpression::genCode(bool preserve) {
    string code;
    string placeStr;
    int stackOffset = callStack->getBaseOffset(id);

    GET_PLACE()
    placeStr = toRegStr(place, preserve ? 's' : 't');

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

string IdExpression::genAddrCode(bool preserve) {
    string code;
    string placeStr;
    int stackOffset = callStack->getBaseOffset(id);

    GET_PLACE()
    placeStr = toRegStr(place, preserve ? 's' : 't');
    
    return stackOffset ?
        code + addi(placeStr, "$fp", stackOffset) :
        code + la(placeStr, id);
}

string TimeExpression::genCode(bool preserve) {
    string code;
    
    GET_PLACE()

    return code + "lw " + toRegStr(place, preserve ? 's' : 't') + ", MS_COUNTER_REG_ADDR\n";
}

string StringExpression::genCode(bool preserve) {
    string code;

    GET_PLACE()

    return code + la(toRegStr(place, preserve ? 's' : 't'), newString(*literal));
}

string IntExpression::genCode(bool preserve) {
    string code;

    GET_PLACE()
    
    return code + "li " + toRegStr(place, preserve ? 's' : 't') + ", " + *literal + "\n";
}

string CharExpression::genCode(bool preserve) {
    string code;

    GET_PLACE()
    
    return code + "li " + toRegStr(place, preserve ? 's' : 't') + ", " + *literal + "\n";
}