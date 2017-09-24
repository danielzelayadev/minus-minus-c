#include "array-declarator.h"
#include "../expressions.h"

ArrayDeclarator::ArrayDeclarator(string id, Expression* dimExpr) : Declarator(id) {
    this->dimExpr = dimExpr;
}

void ArrayDeclarator::checkSemantic(DataType dt) {
    
}

string ArrayDeclarator::toString() {
    string str = id + "[";

    if (dimExpr) str += dimExpr->toString();

    str += "]";

    return str;
}