#ifndef CASTEXPR
#define CASTEXPR

#include "expression.h"
#include "../data-type.h"

class CastExpression : public Expression {
public:
    DataType castType;
    Expression *expr;

    CastExpression(DataType, Expression*);
    string toString();
};

#endif