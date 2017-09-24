#include "var-initializer.h"
#include "../expressions.h"

VarInitializer::VarInitializer(Expression* expr) {
    this->expr = expr;
}

string VarInitializer::toString() {
    return expr->toString();
}