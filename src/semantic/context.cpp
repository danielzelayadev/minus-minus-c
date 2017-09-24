#include "context.h"

Context::Context(VarTable **vtPtr) {
    varTables = new stack<VarTable*>(); 
    varTablePtr = vtPtr; 
}

void Context::enter() {
    varTables->push(((*varTablePtr) = new VarTable((*varTablePtr))));
}

void Context::leave() {
    if (varTables->empty()) return;

    delete (*varTablePtr);
    varTables->pop();
    
    if (!varTables->empty()) (*varTablePtr) = varTables->top();
}