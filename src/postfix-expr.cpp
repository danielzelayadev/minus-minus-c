#include "postfix-expr.h"
#include "memory.h"
#include "helpers.h"
#include "primary-expr.h"

string FunctionCall::genCode() {
    string code;

    for (int i = 0; i < args->size() && i < 4; i++) {
        Expression *expr = (*args)[i];
        code += expr->genCode();
        code += move(toRegStr(i, 'a'), toRegStr(expr->place));
        freeTemp(expr->place);
    }

    code += "jal " + ((IdExpression*)funcExpr)->id + "\n";

    place = newTemp();

    code += move(toRegStr(place), "$v0");

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