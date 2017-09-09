#ifndef UNARYEXPR
#define UNARYEXPR

#include "expr.h"

#define DEFINE_UNARY_EXPR(name) \
class name##Expression : public UnaryExpression { \
public:                                \
    name##Expression(Expression *expr) : UnaryExpression(expr){} \
};

enum UnaryOp {
    PRE_INC,
    PRE_DEC,
    IDENTITY,
    NUM_NEG,
    LOG_NEG,
    BIT_COMPLEMENT,
    DEREF,
    ADDRESSOF
};

class UnaryExpression : public Expression {
public:
    Expression *expr;

    UnaryExpression(Expression *expr) { this->expr = expr; }
};

class SizeofExpression : public UnaryExpression {
public:
    DataType type;

    SizeofExpression(DataType type) : UnaryExpression(0) { this->type = type; }
    SizeofExpression(Expression *expr) : UnaryExpression(expr) { this->type = UNDEF; }
};

DEFINE_UNARY_EXPR(PreIncrement)
DEFINE_UNARY_EXPR(PreDecrement)
DEFINE_UNARY_EXPR(Identity)
DEFINE_UNARY_EXPR(NumericNegation)
DEFINE_UNARY_EXPR(LogicalNegation)
DEFINE_UNARY_EXPR(BitwiseComplement)
DEFINE_UNARY_EXPR(Deref)
DEFINE_UNARY_EXPR(AddressOf)

#endif