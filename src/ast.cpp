#include "ast.h"

CompilationUnit::CompilationUnit() {
    this->globalDecs = new vector<GlobalDeclaration*>();
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

Declaration::Declaration(DataType dataType, vector<InitDeclarator*>*initDecList) {
    this->dataType = dataType;
    this->initDecList = initDecList;
}

Declarator::Declarator(string id, bool isPointer) {
    this->id = id;
    this->isPointer = isPointer;
}

ArrayDeclarator::ArrayDeclarator(string id, bool isPointer, int dims) : Declarator(id, isPointer) {
    this->dimensions = dims;
}

FunctionDeclarator::FunctionDeclarator(string id, bool isPointer, vector<Parameter*>* params) : Declarator(id, isPointer) {
    this->params = params;
}

InitDeclarator::InitDeclarator(Declarator* decl, Initializer* init) {
    this->declarator  = decl;
    this->initializer = init;
}

VarInitializer::VarInitializer(Expression* expr) {
    this->expr = expr;
}

ArrayInitializer::ArrayInitializer(vector<Expression*>* exprList) {
    this->exprList = exprList;
}

Parameter::Parameter(DataType dataType, Declarator *declarator) {
    this->dataType = dataType;
    this->declarator = declarator;
}

string CompilationUnit::toString() {
    stringstream str;

    for (int i = 0; i < globalDecs->size(); i++)
        str << (*globalDecs)[i]->toString();
    
    return str.str();
}