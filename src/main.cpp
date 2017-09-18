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
    if (argc != 3) {
        printf("Usage: %s [ENTRY] [OUTPUT]\n", argv[0]);
        return 1;
    }

    yyin = fopen(argv[1], "r");

    if (!yyin)
        return fileNotFoundErr(argv[1]);

    cout << "Beginning compilation...\n";

    yyparse();

    if (!ast) {
        cout << "Something went wrong while parsing.\n";
        return 1;
    }

    ctx = new Context(&varTable);

    functTable = new FunctionTable();

    ast->checkSemantic();

    if (finishedWithErrors())
        printErrors();
    else {
        ofstream outputFile(argv[2]);
        
        outputFile << ast->genCode() << endl;
        
        outputFile.close();

        cout << "Compiled successfully.\n";
    }

    return 0;
}