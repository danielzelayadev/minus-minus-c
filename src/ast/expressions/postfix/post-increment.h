#ifndef POSTINCR
#define POSTINCR

#include "postfix-expr.h"

class PostIncrement : public PostfixExpression {
public:
    Expression *idExpr;

    PostIncrement(Expression *idExpr) { this->idExpr = idExpr; }

    string genCode(bool = false);
    string toString() { return idExpr->toString() + "--"; }
};

#endif