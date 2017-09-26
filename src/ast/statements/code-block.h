#ifndef CODEBLOCK
#define CODEBLOCK

#include "statement.h"
#include <vector>

using namespace std;

class Declaration;

class CodeBlock : public Statement {
public:
    vector<Declaration*>* declarations;
    vector<Statement*>* statements;

    CodeBlock(vector<Declaration*>* dec, vector<Statement*>* stmts) {
        declarations = dec;
        statements = stmts;
    }

    string genCode();
    string toString();
};

#endif