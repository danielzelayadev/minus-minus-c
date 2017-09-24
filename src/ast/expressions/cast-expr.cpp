#include "cast-expr.h"
#include "../../code-gen/helpers.h"

CastExpression::CastExpression(DataType castType, Expression *expr) {
    this->castType = castType;
    this->expr = expr;
}

string CastExpression::toString() {
    return "(" + mapType(castType) + ")" + expr->toString();
}