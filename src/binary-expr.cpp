#include "binary-expr.h"
#include "memory.h"
#include "helpers.h"

#define GENERIC_BINARY_CODEGEN(name, instr) \
string name##Expression::genCode() { \
    string code; \
    code += left->genCode(); \
    code += right->genCode(); \
    place = left->place; \
    code += string(instr) + " " + toRegStr(place) + ", " + \
    toRegStr(left->place) + ", " + toRegStr(right->place) + "\n"; \
    freeTemp(right->place); \
    return code; \
}

#define MULTIPLICATIVE_BINARY_CODEGEN(name, func) \
string name##Expression::genCode() { \
    string code; \
    code += left->genCode(); \
    code += right->genCode(); \
    place = left->place; \
    code += move("$a0", toRegStr(left->place)); \
    code += move("$a1", toRegStr(right->place)); \
    code += "jal " + string(func) + "\n"; \
    code += move(toRegStr(place), "$v0"); \
    freeTemp(right->place); \
    return code; \
}

BinaryExpression::BinaryExpression(Expression *left, Expression *right, string op) {
    this->left = left;
    this->right = right;
    this->op = op;
}

string AssignmentExpression::genCode() {
    string code;

    code += left->genAddrCode();
    code += right->genCode();

    place = left->place;

    code += sw(toRegStr(right->place), 0, toRegStr(left->place));
    code += move(toRegStr(place), toRegStr(right->place));

    freeTemp(right->place);

    return code;
}

string CondAndExpression::genCode() {
    return "";
}

string CondOrExpression::genCode() {
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
MULTIPLICATIVE_BINARY_CODEGEN(Div, "divide")
MULTIPLICATIVE_BINARY_CODEGEN(Mod, "mod")