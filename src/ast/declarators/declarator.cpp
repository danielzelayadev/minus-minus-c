#include "declarator.h"
#include "../../semantic/symbol-table.h"

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