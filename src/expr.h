#ifndef EXPR
#define EXPR

#include "ast.h"

class Expression : public ASTNode {};

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