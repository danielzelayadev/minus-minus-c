#include "ast.h"
#include "statements.h"
#include "context.h"
#include <stdio.h>

extern Context *ctx;
extern VarTable *varTable;
extern FunctionTable *functTable;

map<string, string> globals;
map<string, string> data;

string mapType(int t) {
    switch (t) {
        case INT:
            return "int";
        case CHAR:
            return "char";
        case VOID:
            return "void";
        case INT_PTR:
            return "int *";
        case CHAR_PTR:
            return "char *";
        case VOID_PTR:
            return "void *";
        default:
            return "";
    }
}

string join(vector<ASTNode*>* ls, string delim) {
    string str;
    int last = ls->size() - 1;

    for (int i = 0; i < ls->size(); i++) {
        ASTNode *node = (*ls)[i];

        str += node->toString();

        if (i != last)
            str += delim;
    }

    return str;
}

string joinMap(map<string, string> *mp, string delim) {
    string str;
    map<string, string>::iterator it = mp->begin();

    while (it != mp->end()) {
        str += it->second;
        if (it != mp->end())
            str += delim;
    }

    return str;
}

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

    code += joinMap(&globals, "\n") + "\n";
    
    code += ".data\n\n";

    code += joinMap(&data, "\n") + "\n";
    
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
    stringstream str;

    for (int i = 0; i < globalDecs->size(); i++)
        str << (*globalDecs)[i]->toString();
    
    return str.str();
}

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

void FunctionDefinition::checkSemantic() {
    // Declare Function o Expand FunctionInfo en el Symbol Table si ya existe
}

string FunctionDefinition::toString() {
    string str = "";

    str += mapType(returnType);
    str += " " + declarator->toString();
    str += cb->toString();
    str += "\n\n";

    return str;
}

Declaration::Declaration(DataType dataType, vector<InitDeclarator*>*initDecList) {
    this->dataType = dataType;
    this->initDecList = initDecList;
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

void FunctionDeclarator::checkSemantic(DataType dt) {

}

string FunctionDeclarator::toString() {
    string str = id + "(";

    str += join((vector<ASTNode*>*)params, ", ");

    str += ")";

    return str;
}

InitDeclarator::InitDeclarator(Declarator* decl, Initializer* init) {
    this->declarator  = decl;
    this->initializer = init;
}

void InitDeclarator::checkSemantic(DataType dt) {

}

string InitDeclarator::toString() {
    string str = declarator->toString();

    if (initializer) str += " = " + initializer->toString();

    return str;
}

VarInitializer::VarInitializer(Expression* expr) {
    this->expr = expr;
}

string VarInitializer::toString() {
    return expr->toString();
}

ArrayInitializer::ArrayInitializer(vector<Expression*>* exprList) {
    this->exprList = exprList;
}

string ArrayInitializer::toString() {
 return "{" + join((vector<ASTNode*>*)exprList, ", ") + "}";
}

Parameter::Parameter(DataType dataType, Declarator *declarator) {
    this->dataType = dataType;
    this->declarator = declarator;
}

string Parameter::toString() {
    string str = mapType(dataType);

    if (declarator) str += " " + declarator->toString();

    return str;
}