#ifndef VARINITIALIZER
#define VARINITIALIZER

#include "initializer.h"
#include <string>

using namespace std;

class Expression;

class VarInitializer : public Initializer {
public:
    Expression* expr;

    VarInitializer(Expression*);
    string toString();
};

#endif