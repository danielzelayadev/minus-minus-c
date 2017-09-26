#ifndef GLOBALDEC
#define GLOBALDEC

#include "../ast-node.h"

class GlobalDeclaration : public ASTNode {
public:
    virtual string genCode() { return ""; }
};

#endif