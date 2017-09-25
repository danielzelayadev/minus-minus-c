#include "id-expr.h"
#include "../../../code-gen/memory.h"
#include "../../../code-gen/helpers.h"

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

int IdExpression::size() {
    return getSize(id);
}