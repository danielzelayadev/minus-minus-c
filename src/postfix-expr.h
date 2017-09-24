#ifndef POSTFIXEXPR
#define POSTFIXEXPR

#include "expr.h"
#include <vector>

using namespace std;

string join(vector<ASTNode*>*, string);

class PostfixExpression : public Expression {};

class ArrayAccess : public PostfixExpression {
public:
    Expression *arrExpr, *accessExpr;

    ArrayAccess(Expression *arrExpr, Expression *accessExpr) {
        this->arrExpr = arrExpr;
        this->accessExpr = accessExpr;
    }
    bool isAssignable() { return true; }
    string toString() {
        return arrExpr->toString() + "[" + accessExpr->toString() + "]";
    }
};

class FunctionCall : public PostfixExpression {
public:
    Expression *funcExpr;
    vector<Expression*> *args;

    FunctionCall(Expression *funcExpr, vector<Expression*> *args) {
        this->funcExpr = funcExpr;
        this->args = args;
    }
    string genCode(bool = false);
    string toString() {
        return funcExpr->toString() + "(" + join((vector<ASTNode*>*)args, ", ") + ")";
    }
};

class PostIncrement : public PostfixExpression {
public:
    Expression *idExpr;

    PostIncrement(Expression *idExpr) { this->idExpr = idExpr; }

    string genCode(bool = false);
    string toString() { return idExpr->toString() + "++"; }
};

class PostDecrement : public PostfixExpression {
public:
    Expression *idExpr;

    PostDecrement(Expression *idExpr) { this->idExpr = idExpr; }

    string toString() { return idExpr->toString() + "--"; }
};

#endif