#include <iostream>
#include <fstream>
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

int fileNotFoundErr(char *file) {
    printf("File '%s' not found.\n", file);
    return 1;
}

int main(int argc, char **argv) {

    ofstream outputFile;

    if (argc != 3) {
        printf("Usage: %s [ENTRY] [OUTPUT]\n", argv[0]);
        return 1;
    }

    yyin = fopen(argv[1], "r");

    if (!yyin)
        return fileNotFoundErr(argv[1]);

    outputFile.open (argv[2]);

    if (outputFile.fail())
        return fileNotFoundErr(argv[2]);

    yyparse();

    ctx = new Context(&varTable);

    functTable = new FunctionTable();

    ast->checkSemantic();

    if (finishedWithErrors())
        printErrors();
    else
        outputFile << ast->genCode() << endl;

    outputFile.close();

    return 0;
}