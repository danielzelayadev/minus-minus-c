#ifndef IDEXPR
#define IDEXPR

#include "primary-expr.h"

class IdExpression : public PrimaryExpression {
public:
    string id;

    IdExpression(string id) { this->id = id; }
    int size();
    bool isAssignable() { return true; }
    string genCode(bool = false);
    string genAddrCode(bool = false);
    string toString() { return id; }
};

#endif