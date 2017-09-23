#include "postfix-expr.h"
#include "memory.h"
#include "helpers.h"
#include "primary-expr.h"
#include <vector>
#include <string.h>

extern Stack *callStack;
bool argsUsed[4];

string FunctionCall::genCode() {
    string code;
    bool origArgsUsed[4];

    memcpy(origArgsUsed, argsUsed, sizeof(bool)*4);

    for (int i = 0; i < args->size() && i < 4; i++) {
        Expression *expr = (*args)[i];
        string argStr = toRegStr(i, 'a');

        code += expr->genCode();

        if (origArgsUsed[i]) {
            callStack->push("--" + argStr, 4);
            code += stackAlloc();
            code += sw(argStr, callStack->getBaseOffset("--"+argStr), "$fp");
        }

        code += move(argStr, toRegStr(expr->place));

        argsUsed[i] = true;

        freeTemp(expr->place);
    }

    code += "jal " + ((IdExpression*)funcExpr)->id + "\n";

    place = newTemp();

    code += move(toRegStr(place), "$v0");

    for (int i = 0; origArgsUsed[i]; i++) {
        string argStr = toRegStr(i, 'a');
        code += lw(argStr, callStack->getBaseOffset("--"+argStr), "$fp");
    }

    memcpy(argsUsed, origArgsUsed, sizeof(bool)*4);

    return code;
}

string PostIncrement::genCode() {
    string code;
    int addrPlace, evalPlace, tmp;

    code += idExpr->genAddrCode();

    addrPlace = idExpr->place;

    code += idExpr->genCode();

    place = idExpr->place;

    tmp = newTemp();

    code += addi(toRegStr(tmp), toRegStr(place), 1);
    code += sw(toRegStr(tmp), 0, toRegStr(addrPlace));

    freeTemp(tmp);
    freeTemp(addrPlace);

    return code;
}