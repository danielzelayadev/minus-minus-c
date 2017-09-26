#include "array-initializer.h"
#include "../../code-gen/helpers.h"

ArrayInitializer::ArrayInitializer(vector<Expression*>* exprList) {
    this->exprList = exprList;
}

string ArrayInitializer::toString() {
 return "{" + join((vector<ASTNode*>*)exprList, ", ") + "}";
}