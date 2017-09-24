#ifndef EXPRSTMT
#define EXPRSTMT

#include "statement.h"
#include "../expressions.h"

class ExpressionStatement : public Statement {
public:
    Expression *expr;

    ExpressionStatement(Expression *expr) { this->expr = expr; }
    string genCode();
    string toString() { return expr->toString() + ";"; }
};

#endif