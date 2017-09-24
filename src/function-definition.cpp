#include "function-definition.h"
#include "helpers.h"
#include "declarators.h"
#include "statements.h"

extern string globalInits;

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

    code += declarator->genCode();

    code += stackAlloc();
    code += sw("$ra", 0, "$sp");

    childCode = cb->genCode();

    if (declarator->id == "main") {
        code += globalInits.size() ? ("\n# global initializations\n" + globalInits) : "";
        code += clearScreen() + "\n";
    }

    code += childCode;

    code += lw("$ra", 0, "$sp");
    code += stackFree();

    code += "\n";

    code += jr();

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
