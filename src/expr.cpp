#include "expr.h"

string mapType(int);

ConditionalExpression::ConditionalExpression(Expression* f, Expression* s, Expression* t) {
    this->first = f;
    this->second = s;
    this->third = t;
}

string ConditionalExpression::toString() {
    return first->toString() + " ? " + second->toString() + " : " + third->toString();
}

CastExpression::CastExpression(DataType castType, Expression *expr) {
    this->castType = castType;
    this->expr = expr;
}

string CastExpression::toString() {
    return "(" + mapType(castType) + ")" + expr->toString();
}