#ifndef AST
#define AST

#include <string>

using namespace std;

enum DataType {
    INT,
    CHAR,
    VOID,
    INT_PTR,
    CHAR_PTR,
    VOID_PTR,
    UNDEF
};

class ASTNode {
public:
    virtual void checkSemantic() {}
    virtual string toString() { return ""; }
};

class GlobalDeclaration : public ASTNode {
public:
    virtual string genCode() { return ""; }
};


#endif