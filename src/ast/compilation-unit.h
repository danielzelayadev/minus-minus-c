#ifndef COMPUNIT
#define COMPUNIT

#include "global/global-declaration.h"
#include <vector>

using namespace std;

class CompilationUnit : public ASTNode {
public:
    vector<GlobalDeclaration*>* globalDecs;

    CompilationUnit();
    void checkSemantic();
    string genCode();
    string toString();
};

#endif // !COMPUNIT