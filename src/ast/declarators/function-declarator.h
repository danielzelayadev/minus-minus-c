#ifndef FUNCDECLARATOR
#define FUNCDECLARATOR

#include "declarator.h"
#include <vector>

class Parameter;

using namespace std;

class FunctionDeclarator : public Declarator {
public:
    vector<Parameter*>* params;
    
    FunctionDeclarator(string, vector<Parameter*>*);

    void checkSemantic(DataType);

    string genCode();
    string toString();
};

#endif