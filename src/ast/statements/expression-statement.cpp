#include "expression-statement.h"

string ExpressionStatement::genCode() {
    string code = expr->genCode();
    if (dynamic_cast<AssignmentExpression*>(expr))
        code += releaseSaved(expr->place);
    else
        freeTemp(expr->place);
    return code;
}