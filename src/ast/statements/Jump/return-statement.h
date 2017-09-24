#ifndef RETSTATEMENT
#define RETSTATEMENT

#include "../statement.h"
#include "../../expressions.h"

class ReturnStatement : public Statement {
public:
    Expression *expr;

    ReturnStatement(Expression *expr = 0) { this->expr = expr; }
    string genCode();
    string toString() { return "return" + (expr ? " " + expr->toString() : "") + ";"; }
};

#endif