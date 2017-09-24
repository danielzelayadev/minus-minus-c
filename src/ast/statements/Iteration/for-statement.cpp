#include "for-statement.h"
#include "../../expressions.h"

string ForStatement::toString() {
    string str = "for (" + initExpr->toString() + "; " + condExpr->toString() + ";";

    if (stepExpr)
        str += stepExpr->toString();

    str += ") " + code->toString();

    return str;
}

string ForStatement::genCode() {
    string code;
    string forLabel = newLabel(".for");
    string endLabel = newLabel(".end_for");

    code += initExpr->genCode();
    freeTemp(initExpr->place);

    code += "\n" + forLabel + ":\n\n";

    code += condExpr->genCode();

    code += "beqz " + toRegStr(condExpr->place) + ", " + endLabel + "\n";
    
    freeTemp(condExpr->place);

    code += this->code->genCode();

    code += stepExpr->genCode();

    freeTemp(stepExpr->place);

    code += "\nj " + forLabel + "\n\n";
    code += endLabel + ":\n\n";

    return code;
}