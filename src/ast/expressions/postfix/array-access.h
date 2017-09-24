#ifndef ARRACCESS
#define ARRACCESS

#include "postfix-expr.h"

class ArrayAccess : public PostfixExpression {
public:
    Expression *arrExpr, *accessExpr;

    ArrayAccess(Expression *arrExpr, Expression *accessExpr) {
        this->arrExpr = arrExpr;
        this->accessExpr = accessExpr;
    }
    bool isAssignable() { return true; }
    string toString() {
        return arrExpr->toString() + "[" + accessExpr->toString() + "]";
    }
};

#endif