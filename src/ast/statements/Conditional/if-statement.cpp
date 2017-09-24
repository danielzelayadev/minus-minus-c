#include "if-statement.h"
#include "../../expressions.h"

string IfStatement::toString() {
    string str = "if (" + condition->toString() + ") " + code->toString();

    if (elseStmt)
        str += "else " + elseStmt->toString();

    return str;
}

string IfStatement::genCode() {
    string code, endIfLabel = newLabel(".end_if");

    code += condition->genCode();
    freeTemp(condition->place);

    if (elseStmt) {
        string elseLabel = newLabel(".else");

        code += "beqz " + toRegStr(condition->place) + ", " + elseLabel + "\n";
        code += this->code->genCode();
        code += "j " + endIfLabel + "\n";
        code += elseLabel + ":\n\n";
        code += elseStmt->genCode();
    } else {
        code += "beqz " + toRegStr(condition->place) + ", " + endIfLabel + "\n";
        code += this->code->genCode();
    }

    code += endIfLabel + ":\n\n";

    return code;
}