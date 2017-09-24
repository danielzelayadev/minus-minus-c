#ifndef BINARYEXPR
#define BINARYEXPR

#include "../expression.h"

#define DEFINE_BINARY_EXPR(name) \
class name##Expression : public BinaryExpression { \
public:                                \
    name##Expression(Expression *left, Expression *right, string op) : BinaryExpression(left, right, op){} \
    string genCode(bool = false); \
    string toString() {\
        return left->toString() + " " + op + " " + right->toString();\
    }\
};

class BinaryExpression : public Expression {
public:
    Expression *left, *right;
    string op;

    BinaryExpression(Expression*, Expression*, string op);
};

DEFINE_BINARY_EXPR(Assignment)
DEFINE_BINARY_EXPR(CondOr)
DEFINE_BINARY_EXPR(CondAnd)
DEFINE_BINARY_EXPR(Or)
DEFINE_BINARY_EXPR(Xor)
DEFINE_BINARY_EXPR(And)
DEFINE_BINARY_EXPR(Equals)
DEFINE_BINARY_EXPR(NotEquals)
DEFINE_BINARY_EXPR(LessThan)
DEFINE_BINARY_EXPR(GreaterThan)
DEFINE_BINARY_EXPR(Lte)
DEFINE_BINARY_EXPR(Gte)
DEFINE_BINARY_EXPR(ShiftRight)
DEFINE_BINARY_EXPR(ShiftLeft)
DEFINE_BINARY_EXPR(Sum)
DEFINE_BINARY_EXPR(Sub)
DEFINE_BINARY_EXPR(Mul)
DEFINE_BINARY_EXPR(Div)
DEFINE_BINARY_EXPR(Mod)

#endif