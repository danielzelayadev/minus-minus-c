#ifndef HELPERS
#define HELPERS

#include <string>
#include <map>
#include "memory.h"

using namespace std;

#define GET_PLACE() \
place = preserve ? newSaved() : newTemp(); \
if (preserve) \
    code += stackPushReg(place, 's');

class Expression;

string newLabel(string = "label");

string move(string, string);

string clearScreen();

string prologue();
string epilogue();

string stackAlloc(int = 4);
string stackFree(int = 4);

string addi(string, string, int);

string la(string, string);

string sw(string = "$t0", int = 0, string = "$fp");
string sb(string = "$t0", int = 0, string = "$fp");
string lw(string = "$t0", int = 0, string = "$fp");
string lb(string = "$t0", int = 0, string = "$fp");

string toRegStr(int, char = 't');

string globalSection(map<string, string>*);
string dataSection(map<string, DataElement>*);

string jumpReturn(Expression* = 0);

string stackPushReg(int, char = 't');

#endif // !HELPERS