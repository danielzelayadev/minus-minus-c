#ifndef POSTFIXEXPR
#define POSTFIXEXPR

#include "expr.h"

class PostfixExpression : public Expression {};

class ArrayAccess : public PostfixExpression {
public:
    Expression *arrExpr, *accessExpr;

    ArrayAccess(Expression *arrExpr, Expression *accessExpr) {
        this->arrExpr = arrExpr;
        this->accessExpr = accessExpr;
    }
};

class FunctionCall : public PostfixExpression {
public:
    Expression *funcExpr;
    vector<Expression*> *args;

    FunctionCall(Expression *funcExpr, vector<Expression*> *args) {
        this->funcExpr = funcExpr;
        this->args = args;
    }
};

class PostIncrement : public PostfixExpression {
public:
    Expression *idExpr;

    PostIncrement(Expression *idExpr) { this->idExpr = idExpr; }
};

class PostDecrement : public PostfixExpression {
public:
    Expression *idExpr;

    PostDecrement(Expression *idExpr) { this->idExpr = idExpr; }
};

#endif