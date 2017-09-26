#include "declaration.h"
#include "../../code-gen/helpers.h"
#include "../declarators.h"

Declaration::Declaration(DataType dataType, vector<InitDeclarator*>*initDecList) {
    this->dataType = dataType;
    this->initDecList = initDecList;
}

string Declaration::genCode() {
    string code;

    for (int i = 0; i < initDecList->size(); i++)
        code += (*initDecList)[i]->genCode(dataType);

    return code;
}

void Declaration::checkSemantic() {
    for (int i = 0; i < initDecList->size(); i++)
        (*initDecList)[i]->checkSemantic(dataType);
}

string Declaration::toString() {
    string str;

    str += mapType(dataType);
    str += " " + join((vector<ASTNode*>*)initDecList, ", ");
    str += ";\n\n";

    return str;
}