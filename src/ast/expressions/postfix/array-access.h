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
    int size();
    bool isAssignable() { return true; }
    string genCode(bool = false);
    string genAddrCode(bool = false);
    string toString() {
        return arrExpr->toString() + "[" + accessExpr->toString() + "]";
    }
};

#endif