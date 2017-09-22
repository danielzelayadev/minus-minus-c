#include "binary-expr.h"
#include "memory.h"
#include "helpers.h"

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