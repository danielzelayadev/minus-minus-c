#ifndef POSTDECR
#define POSTDECR

#include "postfix-expr.h"

class PostDecrement : public PostfixExpression {
public:
    Expression *idExpr;

    PostDecrement(Expression *idExpr) { this->idExpr = idExpr; }

    string toString() { return idExpr->toString() + "--"; }
};

#endif