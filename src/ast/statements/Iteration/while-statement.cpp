#include "while-statement.h"

string WhileStatement::genCode() {
    string code, whileLabel = newLabel(".while"), 
           endLabel = newLabel(".while_end");

    code += whileLabel + ":\n\n";

    code += condition->genCode();

    freeTemp(condition->place);

    code += "beqz " + toRegStr(condition->place) + ", " + endLabel + "\n";

    code += this->code->genCode();

    code += "j " + whileLabel + "\n";

    code += endLabel + ":\n\n";

    return code;
}