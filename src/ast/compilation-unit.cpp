#include "compilation-unit.h"
#include "../code-gen/helpers.h"
#include "../semantic/context.h"

extern Context *ctx;

extern map<string, string> globals;
extern map<string, DataElement> data;

CompilationUnit::CompilationUnit() {
    this->globalDecs = new vector<GlobalDeclaration*>();
}

string CompilationUnit::genCode() {
    string code = "";
    string childCode = "";

    for (int i = 0; i < globalDecs->size(); i++)
        childCode += (*globalDecs)[i]->genCode();
    
    code += "#include \"screen.h\"\n";
    code += "#include \"system.h\"\n\n";

    code += globalSection(&globals) + "\n";
    
    code += ".data\n\n";

    code += dataSection(&data) + "\n\n";
    
    code += ".text\n\n";

    code += childCode;
    
    return code;
}

void CompilationUnit::checkSemantic() {
    ctx->enter();

    for (int i = 0; i < globalDecs->size(); i++)
        (*globalDecs)[i]->checkSemantic();

    ctx->leave();
}

string CompilationUnit::toString() {
    string str;

    for (int i = 0; i < globalDecs->size(); i++)
        str += (*globalDecs)[i]->toString();
    
    return str;
}