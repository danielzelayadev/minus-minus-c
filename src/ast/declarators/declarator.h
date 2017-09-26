#ifndef DECLARATOR
#define DECLARATOR

#include "../ast-node.h"
#include "../data-type.h"

class Declarator : public ASTNode {
public:
    string id;
    bool isPointer;

    Declarator(string);

    virtual void checkSemantic(DataType);

    string toString();
};

#endif