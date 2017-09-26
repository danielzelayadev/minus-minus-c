#include "expression-statement.h"

string ExpressionStatement::genCode() {
    string code = expr->genCode();
    freeTemp(expr->place);
    return code;
}