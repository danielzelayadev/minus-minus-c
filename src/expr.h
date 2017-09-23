#ifndef EXPR
#define EXPR

#include "ast.h"

class Expression : public ASTNode {
public:
    int place;
    virtual string genCode(bool preserve = false) { return ""; }
    virtual bool isAssignable() { return false; }
    virtual string genAddrCode(bool preserve = false) { return ""; }
};

class ConditionalExpression : public Expression {
public:
    Expression *first, *second, *third;

    ConditionalExpression(Expression*, Expression*, Expression*);
    string toString();
};

class CastExpression : public Expression {
public:
    DataType castType;
    Expression *expr;

    CastExpression(DataType, Expression*);
    string toString();
};

#endif