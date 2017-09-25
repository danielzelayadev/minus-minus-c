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
class ASTNode;
class Parameter;

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

string functionPrologue(vector<Parameter*> *params);
string functionEpilogue(bool = false);

string jr(Expression* = 0);

string stackPushReg(int, char = 't');

string mapType(int);
string join(vector<ASTNode*>*, string);

string lreg(int, char = 't');

string useSaved(int*);
string releaseSaved(int);

string allocIntArray(string, int);
string allocCharArray(string, int);

#endif // !HELPERS