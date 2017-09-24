#ifndef WHILESTATEMENT
#define WHILESTATEMENT

#include "../statement.h"
#include "../../expressions.h"

class WhileStatement : public Statement {
public:
    Expression *condition;
    Statement *code;

    WhileStatement(Expression *c, Statement *s) { condition = c; code = s; }
    string genCode();
    string toString() { return "while (" + condition->toString() + ") " + code->toString(); }
};

#endif