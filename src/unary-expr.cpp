#include "unary-expr.h"

string mapType(int);

string mapUnaryOp(int op) {
    switch(op) {
        case IDENTITY:
        return "+";
        case NUM_NEG:
        return "-";
        case LOG_NEG:
        return "!";
        case BIT_COMPLEMENT:
        return "~";
        case ADDRESSOF:
        return "&";
        case DEREF:
        return "*";
        case PRE_DEC:
        return "--";
        case PRE_INC:
        return "++";
        default:
        return "";
    }
}

UnaryExpression *getUnaryInstance(int unaryOp, Expression *expr) {
    switch (unaryOp) {
        case PRE_DEC:
            return new PreDecrementExpression(expr, (UnaryOp)unaryOp);
        case PRE_INC:
            return new PreIncrementExpression(expr, (UnaryOp)unaryOp);
        case IDENTITY:
            return new IdentityExpression(expr, (UnaryOp)unaryOp);
        case NUM_NEG:
            return new NumericNegationExpression(expr, (UnaryOp)unaryOp);
        case LOG_NEG:
            return new LogicalNegationExpression(expr, (UnaryOp)unaryOp);
        case DEREF:
            return new DerefExpression(expr, (UnaryOp)unaryOp);
        case ADDRESSOF:
            return new AddressOfExpression(expr, (UnaryOp)unaryOp);
        case BIT_COMPLEMENT:
            return new BitwiseComplementExpression(expr, (UnaryOp)unaryOp);
        default:
            return 0;
    }
}

string SizeofExpression::toString() {
    string str = "sizeof";

    if (expr)
        str += " " + expr->toString();
    else
        str += "(" + mapType(type) + ")";

    return str;
}