#ifndef FORSTATEMENT
#define FORSTATEMENT

#include "../statement.h"

class Expression;

class ForStatement : public Statement {
public:
    Expression *initExpr, *condExpr, *stepExpr;
    Statement *code;

    ForStatement(Expression *ie, Expression *ce, Expression *se, Statement *cd) {
        initExpr = ie;
        condExpr = ce;
        stepExpr = se;
        code     = cd;
    }
    string genCode();
    string toString();
};

#endif