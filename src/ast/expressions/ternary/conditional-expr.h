#ifndef CONDEXPR
#define CONDEXPR

#include "../expression.h"

class ConditionalExpression : public Expression {
public:
    Expression *first, *second, *third;

    ConditionalExpression(Expression*, Expression*, Expression*);
    string toString();
};

#endif