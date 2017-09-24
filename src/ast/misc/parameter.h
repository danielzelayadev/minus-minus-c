#ifndef PARAMETER
#define PARAMETER

#include "../ast-node.h"
#include "../data-type.h"

class Declarator;

class Parameter : ASTNode {
public:
    DataType dataType;
    Declarator* declarator;

    Parameter(DataType, Declarator*);
    string toString();
};

#endif