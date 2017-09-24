#ifndef CONTSTATEMENT
#define CONTSTATEMENT

#include "../statement.h"

class ContinueStatement : public Statement {
public:
    string toString() { return "continue;"; }
};

#endif