#include "expr.h"

ConditionalExpression::ConditionalExpression(Expression* f, Expression* s, Expression* t) {
    this->first = f;
    this->second = s;
    this->third = t;
}

CastExpression::CastExpression(DataType castType, Expression *expr) {
    this->castType = castType;
    this->expr = expr;
}