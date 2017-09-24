#ifndef DECLARATORS
#define DECLARATORS

#include "ast.h"
#include <vector>

using namespace std;

class Expression;
class Parameter;

class Declarator : public ASTNode {
public:
    string id;
    bool isPointer;

    Declarator(string);

    virtual void checkSemantic(DataType);

    string toString();
};

class ArrayDeclarator : public Declarator {
public:
    Expression *dimExpr;

    ArrayDeclarator(string, Expression*);

    void checkSemantic(DataType);

    string toString();
};

class FunctionDeclarator : public Declarator {
public:
    vector<Parameter*>* params;
    
    FunctionDeclarator(string, vector<Parameter*>*);

    void checkSemantic(DataType);

    string genCode();
    string toString();
};

#endif