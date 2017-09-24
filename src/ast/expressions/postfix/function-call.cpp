#include "function-call.h"
#include "../../../code-gen/memory.h"
#include "../../../code-gen/helpers.h"
#include "../primary.h"
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

    for (int i = 0; origArgsUsed[i]; i++)
        code += lreg(i, 'a');

    memcpy(argsUsed, origArgsUsed, sizeof(bool)*4);

    return code;
}