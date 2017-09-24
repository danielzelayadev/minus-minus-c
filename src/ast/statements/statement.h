#ifndef STATEMENT
#define STATEMENT

#include "../ast-node.h"

class Statement : public ASTNode {
public:
    virtual string genCode() { return ""; }
};

#endif // !STATEMENT