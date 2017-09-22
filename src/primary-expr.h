#ifndef PRIMARYEXPR
#define PRIMARYEXPR

#include "expr.h"

#define DEFINE_LITERAL_EXPR(name) \
class name##Expression : public PrimaryExpression { \
public:                                \
    string *literal;                    \
    name##Expression(string *literal) { this->literal = literal; } \
    string genCode(); \
    string toString() { return *literal; } \
};

class PrimaryExpression : public Expression {};

class IdExpression : public PrimaryExpression {
public:
    string id;

    IdExpression(string id) { this->id = id; }
    bool isAssignable() { return true; }
    string genCode();
    string genAddrCode();
    string toString() { return id; }
};

DEFINE_LITERAL_EXPR(Int)
DEFINE_LITERAL_EXPR(Char)
DEFINE_LITERAL_EXPR(String)

#endif