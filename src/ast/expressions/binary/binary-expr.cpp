#include "binary-expr.h"
#include "../../../code-gen/memory.h"
#include "../../../code-gen/helpers.h"
#include "../postfix.h"
#include "../primary.h"

#define GET_BINARY_PLACE() \
if (preserve && leftIsSaved || \
   !preserve && !leftIsSaved) place = left->place; \
else if (preserve && !leftIsSaved) {\
    useSaved(&place); \
    freeTemp(left->place); \
} \
else if (!preserve && leftIsSaved) { \
    place = newTemp(); \
    releaseSaved(left->place); \
}

#define GENERIC_BINARY_CODEGEN(name, instr) \
string name##Expression::genCode(bool preserve) { \
    string code; \
    bool leftIsSaved = dynamic_cast<FunctionCall*>(right); \
    code += left->genCode(leftIsSaved); \
    code += right->genCode(); \
    GET_BINARY_PLACE() \
    code += string(instr) + " " + toRegStr(place, preserve ? 's' : 't') + ", " + \
    toRegStr(left->place, leftIsSaved ? 's' : 't') + ", " + toRegStr(right->place) + "\n"; \
    freeTemp(right->place); \
    return code; \
}

#define MULTIPLICATIVE_BINARY_CODEGEN(name, func) \
string name##Expression::genCode(bool preserve) { \
    vector<Expression*> args; \
    args.push_back(left); \
    args.push_back(right); \
    FunctionCall fc(new IdExpression(func), &args);\
    string code = fc.genCode(preserve);\
    place = fc.place; \
    return code; \
}

BinaryExpression::BinaryExpression(Expression *left, Expression *right, string op) {
    this->left = left;
    this->right = right;
    this->op = op;
}

string AssignmentExpression::genCode(bool preserve) {
    string code;
    bool leftIsSaved = true;

    code += left->genAddrCode(leftIsSaved);
    code += right->genCode();

    GET_BINARY_PLACE()

    code += sw(toRegStr(right->place), 0, toRegStr(left->place, 's'));
    code += move(toRegStr(place, preserve ? 's' : 't'), toRegStr(right->place));

    freeTemp(right->place);

    return code;
}

string CondAndExpression::genCode(bool preserve) {
    return "";
}

string CondOrExpression::genCode(bool preserve) {
    return "";
}

GENERIC_BINARY_CODEGEN(Or, "or")
GENERIC_BINARY_CODEGEN(Xor, "xor")
GENERIC_BINARY_CODEGEN(And, "and")
GENERIC_BINARY_CODEGEN(Equals, "seq")
GENERIC_BINARY_CODEGEN(NotEquals, "sne")
GENERIC_BINARY_CODEGEN(LessThan, "slt")
GENERIC_BINARY_CODEGEN(GreaterThan, "sgt")
GENERIC_BINARY_CODEGEN(Lte, "sle")
GENERIC_BINARY_CODEGEN(Gte, "sge")
GENERIC_BINARY_CODEGEN(ShiftLeft, "sll")
GENERIC_BINARY_CODEGEN(ShiftRight, "slr")
GENERIC_BINARY_CODEGEN(Sum, "add")
GENERIC_BINARY_CODEGEN(Sub, "sub")

MULTIPLICATIVE_BINARY_CODEGEN(Mul, "mult")
MULTIPLICATIVE_BINARY_CODEGEN(Div, "div")
MULTIPLICATIVE_BINARY_CODEGEN(Mod, "mod")