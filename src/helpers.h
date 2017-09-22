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

string stackStoreW(string = "$t0", int = 0);
string stackStoreB(string = "$t0", int = 0);
string stackLoadW(string  = "$t0", int = 0);
string stackLoadB(string  = "$t0", int = 0);
string stackAlloc(int = 4);
string stackFree(int = 4);

string jumpReturn(Expression* = 0);

#endif // !HELPERS