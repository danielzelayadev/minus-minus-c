#ifndef SYMBOLTABLE
#define SYMBOLTABLE

#include <map>
#include <stack>
#include <vector>
#include <string>

#include "ast.h"

using namespace std;

class Symbol {
public:
    string id;

    Symbol(string id) { this->id = id; }
};

class Variable : public Symbol {
public:
    DataType type;

    Variable(DataType type, string id) : Symbol(id) { this->type = type; }
};
class Function : public Symbol {
public:
    DataType returnType;

    Function(DataType rt, string id) : Symbol(id) { returnType = rt; }
};

class SymbolTable {};

class VarTable : public SymbolTable {
private:
    vector<Variable*> *variables;
    VarTable *parent;

    friend class Context;

    VarTable(VarTable*);
public:
    VarTable();

    void declare(Variable*);

    Variable *lookup(string);
    Variable *lookupLocally(string);

    bool exists(string);
    bool existsLocally(string);
};

class FunctionTable : public SymbolTable {
private:
    vector<Function*> *functs;
public:
    FunctionTable();

    void declare(Function*);

    Function *lookup(string);
    
    bool exists(string);
};

#endif // !SYMBOLTABLE