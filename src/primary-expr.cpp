#include "primary-expr.h"
#include "helpers.h"

string newString(string);

string StringExpression::genCode() {
    string code;

    code += "lw $t0, " + newString(literal) + "\n";

    return code;
}