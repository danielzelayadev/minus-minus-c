#include "statements.h"
#include "binary-expr.h"
#include "helpers.h"
#include "memory.h"
#include <iostream>

extern Stack *callStack;
extern int currScope;

string join(vector<ASTNode*>*, string);

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

string IfStatement::toString() {
    string str = "if (" + condition->toString() + ") " + code->toString();

    if (elseStmt)
        str += "else " + elseStmt->toString();

    return str;
}

string ForStatement::toString() {
    string str = "for (" + initExpr->toString() + "; " + condExpr->toString() + ";";

    if (stepExpr)
        str += stepExpr->toString();

    str += ") " + code->toString();

    return str;
}

string ExpressionStatement::genCode() {
    string code = expr->genCode();
    if (dynamic_cast<AssignmentExpression*>(expr))
        freeSaved(expr->place);
    else
        freeTemp(expr->place);
    return code;
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