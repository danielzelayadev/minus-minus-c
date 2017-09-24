#include "function-definition.h"
#include "../../code-gen/memory.h"
#include "../../code-gen/helpers.h"
#include "../declarators.h"
#include "../statements.h"
#include "../misc.h"

extern string globalInits;
extern Stack *callStack;

int currParamCount;

FunctionDefinition::FunctionDefinition(FunctionDeclarator* declarator, CodeBlock* cb) {
    this->returnType = INT;
    this->declarator = declarator;
    this->cb = cb;
}

FunctionDefinition::FunctionDefinition(DataType returnType, FunctionDeclarator* declarator, CodeBlock* cb) {
    this->returnType = returnType;
    this->declarator = declarator;
    this->cb = cb;
}

string FunctionDefinition::genCode() {
    string code;
    string childCode;
    FunctionDeclarator *decl = (FunctionDeclarator*)declarator;

    currParamCount = decl->params->size();

    code += decl->genCode();

    code += functionPrologue(decl->params);

    childCode = cb->genCode();

    if (declarator->id == "main") {
        code += globalInits.size() ? ("\n# global initializations\n" + globalInits) : "";
        code += clearScreen() + "\n";
    }

    code += childCode;

    code += functionEpilogue(currParamCount);

    return code;
}

void FunctionDefinition::checkSemantic() {
}

string FunctionDefinition::toString() {
    string str = "";

    str += mapType(returnType);
    str += " " + declarator->toString();
    str += cb->toString();
    str += "\n\n";

    return str;
}
