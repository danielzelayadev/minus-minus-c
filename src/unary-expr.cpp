#include "unary-expr.h"

UnaryExpression *getUnaryInstance(int unaryOp, Expression *expr) {
    switch (unaryOp) {
        case PRE_DEC:
            return new PreDecrementExpression(expr);
        case PRE_INC:
            return new PreIncrementExpression(expr);
        case IDENTITY:
            return new IdentityExpression(expr);
        case NUM_NEG:
            return new NumericNegationExpression(expr);
        case LOG_NEG:
            return new LogicalNegationExpression(expr);
        case DEREF:
            return new DerefExpression(expr);
        case ADDRESSOF:
            return new AddressOfExpression(expr);
        case BIT_COMPLEMENT:
            return new BitwiseComplementExpression(expr);
        default:
            return 0;
    }
}