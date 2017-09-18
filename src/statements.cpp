#include "statements.h"
#include "helpers.h"

string join(vector<ASTNode*>*, string);

string CodeBlock::genCode() {
    string code;

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