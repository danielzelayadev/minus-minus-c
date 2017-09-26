#ifndef ASTNODE
#define ASTNODE

#include <string>

using namespace std;

class ASTNode {
public:
    virtual void checkSemantic() {}
    virtual string toString() { return ""; }
};

#endif