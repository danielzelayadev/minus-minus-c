#include "initializers.h"
#include "helpers.h"

VarInitializer::VarInitializer(Expression* expr) {
    this->expr = expr;
}

string VarInitializer::toString() {
    return expr->toString();
}

ArrayInitializer::ArrayInitializer(vector<Expression*>* exprList) {
    this->exprList = exprList;
}

string ArrayInitializer::toString() {
 return "{" + join((vector<ASTNode*>*)exprList, ", ") + "}";
}