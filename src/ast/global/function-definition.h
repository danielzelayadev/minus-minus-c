#ifndef FUNCDEF
#define FUNCDEF

#include "global-declaration.h"
#include "../data-type.h"

class FunctionDeclarator;
class CodeBlock;

class FunctionDefinition : public GlobalDeclaration {
public:
    DataType returnType;
    FunctionDeclarator* declarator;
    CodeBlock* cb;

    FunctionDefinition(DataType returnType, FunctionDeclarator* declarator, CodeBlock* cb);
    FunctionDefinition(FunctionDeclarator* declarator, CodeBlock* cb);

    void checkSemantic();

    string genCode();
    string toString();
};

#endif