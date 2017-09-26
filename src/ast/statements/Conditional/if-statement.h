#ifndef IFSTATEMENT
#define IFSTATEMENT

#include "../statement.h"

class Expression;

class IfStatement : public Statement {
public:
    Expression *condition;
    Statement *code, *elseStmt;

    IfStatement(Expression *condition, Statement *code, Statement *elseStmt = 0) {
        this->condition = condition;
        this->code = code;
        this->elseStmt = elseStmt;
    }
    string genCode();
    string toString();
};

#endif