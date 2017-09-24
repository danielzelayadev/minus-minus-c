#include "function-declarator.h"
#include "../../code-gen/memory.h"
#include "../../code-gen/helpers.h"

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