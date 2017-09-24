#ifndef INITIALIZERS
#define INITIALIZERS

#include "expr.h"
#include <vector>

using namespace std;

class Initializer : public ASTNode {};

class VarInitializer : public Initializer {
public:
    Expression* expr;

    VarInitializer(Expression*);
    string toString();
};

class ArrayInitializer : public Initializer {
public:
    vector<Expression*>* exprList;

    ArrayInitializer(vector<Expression*>*);
    string toString();
};

#endif