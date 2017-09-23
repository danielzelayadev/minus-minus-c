#ifndef PRIMARYEXPR
#define PRIMARYEXPR

#include "expr.h"

#define DEFINE_LITERAL_EXPR(name) \
class name##Expression : public PrimaryExpression { \
public:                                \
    string *literal;                    \
    name##Expression(string *literal) { this->literal = literal; } \
    string genCode(bool = false); \
    string toString() { return *literal; } \
};

class PrimaryExpression : public Expression {};

class IdExpression : public PrimaryExpression {
public:
    string id;

    IdExpression(string id) { this->id = id; }
    bool isAssignable() { return true; }
    string genCode(bool = false);
    string genAddrCode(bool = false);
    string toString() { return id; }
};

class TimeExpression : public PrimaryExpression {
public:
    string genCode(bool = false);
    string toString() { return "time(0)"; }
};

DEFINE_LITERAL_EXPR(Int)
DEFINE_LITERAL_EXPR(Char)
DEFINE_LITERAL_EXPR(String)

#endif