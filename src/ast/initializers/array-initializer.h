#ifndef ARRAYINITIALIZER
#define ARRAYINITIALIZER

#include "initializer.h"
#include <vector>

using namespace std;

class Expression;

class ArrayInitializer : public Initializer {
public:
    vector<Expression*>* exprList;

    ArrayInitializer(vector<Expression*>*);
    string toString();
};

#endif