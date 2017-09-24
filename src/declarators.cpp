#include "declarators.h"
#include "expr.h"
#include "helpers.h"
#include "memory.h"
#include "symbol-table.h"

extern VarTable *varTable;

Declarator::Declarator(string id) {
    this->id = id;
    this->isPointer = false;
}

void Declarator::checkSemantic(DataType dt) {
    varTable->declare(new Variable((DataType)(dt + (isPointer ? 3 : 0)), id));
}

string Declarator::toString() {
    string str;

    if (isPointer) str += "*";
    str += id;

    return str;
}

ArrayDeclarator::ArrayDeclarator(string id, Expression* dimExpr) : Declarator(id) {
    this->dimExpr = dimExpr;
}

void ArrayDeclarator::checkSemantic(DataType dt) {
    
}

string ArrayDeclarator::toString() {
    string str = id + "[";

    if (dimExpr) str += dimExpr->toString();

    str += "]";

    return str;
}

FunctionDeclarator::FunctionDeclarator(string id, vector<Parameter*>* params) : Declarator(id) {
    this->params = params;
}

string FunctionDeclarator::genCode() {
    string code;

    code += id + ":\n\n";

    newGlobal(id);

    return code;
}

void FunctionDeclarator::checkSemantic(DataType dt) {

}

string FunctionDeclarator::toString() {
    string str = id + "(";

    str += join((vector<ASTNode*>*)params, ", ");

    str += ")";

    return str;
}