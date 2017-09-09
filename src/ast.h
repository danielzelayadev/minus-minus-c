#ifndef AST
#define AST

#include <string>
#include <vector>
#include <sstream>

using namespace std;

class GlobalDeclaration;
class Expression;
class CodeBlock;
class FunctionDeclarator;
class InitDeclarator;
class Parameter;
class Initializer;

enum DataType {
    INT,
    CHAR,
    VOID,
    INT_PTR,
    CHAR_PTR,
    VOID_PTR,
    UNDEF
};

class ASTNode {
public:
    virtual string toString() {
        return "";
    }
};

class CompilationUnit : public ASTNode {
public:
    vector<GlobalDeclaration*>* globalDecs;

    CompilationUnit();
    string toString();
};

class GlobalDeclaration : public ASTNode {};

class FunctionDefinition : public GlobalDeclaration {
public:
    DataType returnType;
    FunctionDeclarator* declarator;
    CodeBlock* cb;

    FunctionDefinition(DataType returnType, FunctionDeclarator* declarator, CodeBlock* cb);
    FunctionDefinition(FunctionDeclarator* declarator, CodeBlock* cb);

    string toString();
};

class Declaration : public GlobalDeclaration {
public:
    DataType dataType;
    vector<InitDeclarator*>* initDecList;

    Declaration(DataType, vector<InitDeclarator*>* = 0);

    string toString();
};





class Declarator : public ASTNode {
public:
    string id;
    bool isPointer;

    Declarator(string);

    string toString();
};

class ArrayDeclarator : public Declarator {
public:
    Expression *dimExpr;

    ArrayDeclarator(string, Expression*);

    string toString();
};

class FunctionDeclarator : public Declarator {
public:
    vector<Parameter*>* params;
    
    FunctionDeclarator(string, vector<Parameter*>*);

    string toString();
};

class InitDeclarator : public ASTNode {
public:
    Declarator* declarator;
    Initializer* initializer;

    InitDeclarator(Declarator*, Initializer*);

    string toString();
};




class Initializer : public ASTNode {};

class VarInitializer : public Initializer {
public:
    Expression* expr;

    VarInitializer(Expression*);
    string toString();
};

class ArrayInitializer : public Initializer {
public:
    vector<Expression*>* exprList;

    ArrayInitializer(vector<Expression*>*);
    string toString();
};






class Parameter : ASTNode {
public:
    DataType dataType;
    Declarator* declarator;

    Parameter(DataType, Declarator*);
    string toString();
};

#endif