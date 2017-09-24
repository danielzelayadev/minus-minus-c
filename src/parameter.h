#ifndef PARAMETER
#define PARAMETER

#include "declarators.h"

class Parameter : ASTNode {
public:
    DataType dataType;
    Declarator* declarator;

    Parameter(DataType, Declarator*);
    string toString();
};

#endif