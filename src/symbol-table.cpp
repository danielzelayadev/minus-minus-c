#include "symbol-table.h"

VarTable::VarTable(VarTable *p) {
    variables = new vector<Variable*>();
    parent = p;
}

VarTable::VarTable() {
    variables = new vector<Variable*>();
    parent = 0;
}

void VarTable::declare(Variable *v) {
    variables->push_back(v);
}

Variable *VarTable::lookup(string id) {
    Variable *res = lookupLocally(id);
    return res ? res : (parent ? parent->lookup(id) : 0);
}

Variable *VarTable::lookupLocally(string id) {
    for (int i = 0; i < variables->size(); i++)
        if ((*variables)[i]->id == id)
            return (*variables)[i];

    return 0;
}

bool VarTable::exists(string id) {
    return lookup(id);
}

bool VarTable::existsLocally(string id) {
    return lookupLocally(id);
}

FunctionTable::FunctionTable() {
    functs = new vector<Function*>();
}

void FunctionTable::declare(Function *f) {
    functs->push_back(f);
}

Function *FunctionTable::lookup(string id) {
    for (int i = 0; i < functs->size(); i++)
        if ((*functs)[i]->id == id)
            return (*functs)[i];
        
    return 0;
}

bool FunctionTable::exists(string id) {
    return lookup(id);
}