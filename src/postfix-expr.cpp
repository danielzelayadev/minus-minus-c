#include "postfix-expr.h"
#include "memory.h"
#include "helpers.h"
#include "primary-expr.h"
#include <vector>
#include <string.h>

extern Stack *callStack;
bool argsUsed[4];

string FunctionCall::genCode(bool preserve) {
    string code;
    bool origArgsUsed[4];

    memcpy(origArgsUsed, argsUsed, sizeof(bool)*4);

    for (int i = 0; i < args->size() && i < 4; i++) {
        Expression *expr = (*args)[i];
        string argStr = toRegStr(i, 'a');

        code += expr->genCode();

        if (origArgsUsed[i]) code += stackPushReg(i, 'a');

        code += move(argStr, toRegStr(expr->place));

        argsUsed[i] = true;

        freeTemp(expr->place);
    }

    code += "jal " + ((IdExpression*)funcExpr)->id + "\n";

    GET_PLACE()

    code += move(toRegStr(place), "$v0");

    for (int i = 0; origArgsUsed[i]; i++) {
        string argStr = toRegStr(i, 'a');
        code += lw(argStr, callStack->getBaseOffset("--"+argStr), "$fp");
    }

    memcpy(argsUsed, origArgsUsed, sizeof(bool)*4);

    return code;
}

string PostIncrement::genCode(bool preserve) {
    string code;
    int addrPlace, evalPlace, tmp;

    code += idExpr->genAddrCode();

    addrPlace = idExpr->place;

    code += idExpr->genCode();

    place = preserve ? newSaved() : idExpr->place;
    if (preserve) {
        code += stackPushReg(place, 's');
        code += move(toRegStr(place, 's'), toRegStr(idExpr->place));
        freeTemp(idExpr->place);
    }

    tmp = newTemp();

    code += addi(toRegStr(tmp), toRegStr(place), 1);
    code += sw(toRegStr(tmp), 0, toRegStr(addrPlace));

    freeTemp(tmp);
    freeTemp(addrPlace);

    return code;
}