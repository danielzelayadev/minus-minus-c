#ifndef CONTEXT
#define CONTEXT

#include "symbol-table.h"

class Context {
private:
    stack<VarTable*> *varTables;
    VarTable **varTablePtr;
public:
    Context(VarTable**);
    void enter();
    void leave();
};

#endif