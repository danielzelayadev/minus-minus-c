#ifndef STATEMENT
#define STATEMENT

#include "expr.h"

class Statement : public ASTNode {};

class CodeBlock : public Statement {
public:
    vector<Declaration*>* declarations;
    vector<Statement*>* statements;

    CodeBlock(vector<Declaration*>* dec, vector<Statement*>* stmts) {
        declarations = dec;
        statements = stmts;
    }

    string genCode();
    string toString();
};

class ExpressionStatement : public Statement {
public:
    Expression *expr;

    ExpressionStatement(Expression *expr) { this->expr = expr; }
    string toString() { return expr->toString() + ";"; }
};

class IfStatement : public Statement {
public:
    Expression *condition;
    Statement *code, *elseStmt;

    IfStatement(Expression *condition, Statement *code, Statement *elseStmt = 0) {
        this->condition = condition;
        this->code = code;
        this->elseStmt = elseStmt;
    }
    string toString();
};

class WhileStatement : public Statement {
public:
    Expression *condition;
    Statement *code;

    WhileStatement(Expression *c, Statement *s) { condition = c; code = s; }
    string toString() { return "while (" + condition->toString() + ") " + code->toString(); }
};

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
    string toString();
};

class ContinueStatement : public Statement {
public:
    string toString() { return "continue;"; }
};
class BreakStatement : public Statement {
public:
    string toString() { return "break;"; }
};

class ReturnStatement : public Statement {
public:
    Expression *expr;

    ReturnStatement(Expression *expr = 0) { this->expr = expr; }
    string toString() { return "return" + (expr ? " " + expr->toString() : "") + ";"; }
};

#endif // !STATEMENT