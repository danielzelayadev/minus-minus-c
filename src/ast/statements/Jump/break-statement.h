#ifndef BREAKSTATEMENT
#define BREAKSTATEMENT

#include "../statement.h"

class BreakStatement : public Statement {
public:
    string toString() { return "break;"; }
};

#endif