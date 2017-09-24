#include "code-block.h"
#include "../global.h"
#include "../../code-gen/helpers.h"

extern Stack *callStack;
extern int currScope;

string CodeBlock::genCode() {
    string code;

    currScope++;

    callStack->pushFrame();

    code += prologue();

    for (int i = 0; i < declarations->size(); i++)
        code += (*declarations)[i]->genCode();

    code += "\n";
    
    for (int i = 0; i < statements->size(); i++)
        code += (*statements)[i]->genCode();

    callStack->popFrame();

    code += epilogue();

    currScope--;

    return code;
}

string CodeBlock::toString() {
    string str = "{";

    if (declarations->size() || statements->size()) {
        str += "\n\t";
        str += join((vector<ASTNode*>*)declarations, "\t");
        str += join((vector<ASTNode*>*)statements, "\n\t");
    }

    str += "}";

    return str;
}