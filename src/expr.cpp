#include "expr.h"

ConditionalExpression::ConditionalExpression(Expression* f, Expression* s, Expression* t) {
    this->first = f;
    this->second = s;
    this->third = t;
}