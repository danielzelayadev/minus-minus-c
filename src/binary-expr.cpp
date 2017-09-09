#include "binary-expr.h"

BinaryExpression::BinaryExpression(Expression *left, Expression *right, string op) {
    this->left = left;
    this->right = right;
    this->op = op;
}