#ifndef INITDECl
#define INITDECl

#include "ast.h"

class Initializer;
class Declarator;

class InitDeclarator : public ASTNode {
public:
    Declarator* declarator;
    Initializer* initializer;

    InitDeclarator(Declarator*, Initializer*);

    void checkSemantic(DataType);

    string genCode(DataType);
    string toString();
};

#endif