#ifndef  DECLARATION
#define  DECLARATION

#include "ast.h"
#include <vector>

using namespace std;

class InitDeclarator;

class Declaration : public GlobalDeclaration {
public:
    DataType dataType;
    vector<InitDeclarator*>* initDecList;

    Declaration(DataType, vector<InitDeclarator*>* = 0);

    void checkSemantic();

    string genCode();
    string toString();
};

#endif // ! DECLARATION