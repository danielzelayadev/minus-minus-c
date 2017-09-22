#ifndef HELPERS
#define HELPERS

#include <string>

using namespace std;

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

string jumpReturn(Expression* = 0);

#endif // !HELPERS