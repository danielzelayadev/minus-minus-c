#include "array-access.h"
#include "../primary.h"
#include "../../../code-gen/memory.h"
#include "../../../code-gen/helpers.h"

extern Stack *callStack;

string ArrayAccess::genAddrCode(bool preserve) {
    string code;
    string id = ((IdExpression*)arrExpr)->id;
    string placeStr, baseStr, accessStr;

    code += arrExpr->genAddrCode(true);

    baseStr = toRegStr(arrExpr->place, 's');

    code += accessExpr->genCode();

    accessStr = toRegStr(accessExpr->place);

    code += "move $a0, " + accessStr + "\n";
    code += "li $a1, " + to_string(size()) + "\n";
    code += "jal mult\n";

    freeTemp(accessExpr->place);

    place = preserve ? arrExpr->place : newTemp();

    placeStr = toRegStr(place, preserve ? 's' : 't');

    code += "sub " + placeStr + ", " + baseStr + ", $v0\n";

    if (!preserve) code += releaseSaved(arrExpr->place);

    return code;
}

int ArrayAccess::size() {
    return getSize(((IdExpression*)arrExpr)->id+"[0]");
}