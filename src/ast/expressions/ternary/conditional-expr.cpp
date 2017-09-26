#include "conditional-expr.h"

ConditionalExpression::ConditionalExpression(Expression* f, Expression* s, Expression* t) {
    this->first = f;
    this->second = s;
    this->third = t;
}

string ConditionalExpression::toString() {
    return first->toString() + " ? " + second->toString() + " : " + third->toString();
}