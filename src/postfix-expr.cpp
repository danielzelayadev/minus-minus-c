#include "postfix-expr.h"
#include "memory.h"
#include "helpers.h"
#include "primary-expr.h"

string FunctionCall::genCode() {
    string code;

    for (int i = 0; i < args->size() && i < 4; i++) {
        Expression *expr = (*args)[i];
        code += expr->genCode();
        code += move("$a" + to_string(i), "$t" + to_string(expr->place));
        freeTemp(expr->place);
    }

    code += "jal " + ((IdExpression*)funcExpr)->id + "\n";

    place = newTemp();

    code += move("$t" + to_string(place), "$v0");

    return code;
}