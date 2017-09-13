#include <iostream>
#include <stdio.h>
#include "ast.h"
#include "context.h"
#include "errors.h"

using namespace std;

Context *ctx;
VarTable *varTable;
FunctionTable *functTable;

extern CompilationUnit* ast;

extern FILE* yyin;

int yyparse();

int main(int argc, char **argv) {

    if (argc != 2) {
        printf("Usage: %s [FILE]\n", argv[0]);
        return 1;
    }

    yyin = fopen(argv[1], "r");

    if (!yyin) {
        printf("File '%s' not found.\n", argv[1]);
        return 1;
    }

    yyparse();

    ctx = new Context(&varTable);

    functTable = new FunctionTable();

    ast->checkSemantic();

    if (finishedWithErrors())
        printErrors();

    return 0;
}