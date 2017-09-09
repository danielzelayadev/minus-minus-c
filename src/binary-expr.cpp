#include "binary-expr.h"

BinaryExpression::BinaryExpression(Expression *left, Expression *right) {
    this->left = left;
    this->right = right;
}