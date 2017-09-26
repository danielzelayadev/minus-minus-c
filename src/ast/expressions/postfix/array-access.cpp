#include "array-access.h"
#include "../primary.h"
#include "../binary.h"
#include "../../../code-gen/memory.h"
#include "../../../code-gen/helpers.h"

extern Stack *callStack;

string ArrayAccess::genCode(bool preserve) {
    string code, placeStr;

    code += genAddrCode(preserve);
    placeStr = toRegStr(place, preserve ? 's' : 't');
    code += size() == 4 ? lw( placeStr, 0, placeStr) : lb( placeStr, 0, placeStr);

    return code;
}

string ArrayAccess::genAddrCode(bool preserve) {
    string code;
    string placeStr, baseStr, offsetStr;
    MulExpression offsetExpr(accessExpr, 
        new IntExpression(new string(to_string(size()))), "*");
    bool isLocal = callStack->getBaseOffset(((IdExpression*)arrExpr)->id) != 0;

    code += arrExpr->genAddrCode(true);

    baseStr = toRegStr(arrExpr->place, 's');

    if (isLocal) code += lw(baseStr, 0, baseStr);

    code += offsetExpr.genCode();

    offsetStr = toRegStr(offsetExpr.place);

    place = preserve ? arrExpr->place : newTemp();

    placeStr = toRegStr(place, preserve ? 's' : 't');

    code += (isLocal ? "sub " : "add ") + 
        placeStr + ", " + baseStr + ", "+ offsetStr + "\n";

    freeTemp(offsetExpr.place);

    if (!preserve) code += releaseSaved(arrExpr->place);

    return code;
}

int ArrayAccess::size() {
    return getSize(((IdExpression*)arrExpr)->id, true);
}