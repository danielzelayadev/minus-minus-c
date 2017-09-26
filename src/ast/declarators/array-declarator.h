#ifndef ARRAYDECLARATOR
#define ARRAYDECLARATOR

#include "declarator.h"

class Expression;

class ArrayDeclarator : public Declarator {
public:
    Expression *dimExpr;

    ArrayDeclarator(string, Expression*);

    void checkSemantic(DataType);

    string toString();
};

#endif