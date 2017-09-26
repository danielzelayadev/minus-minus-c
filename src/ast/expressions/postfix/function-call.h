#ifndef FUNCALL
#define FUNCALL

#include "postfix-expr.h"
#include "../../../code-gen/helpers.h"
#include <vector>

using namespace std;

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

#endif