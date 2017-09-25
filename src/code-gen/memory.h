#ifndef  MEMORY
#define  MEMORY

#include <string>
#include <vector>

using namespace std;

class StackData {
public:
    string id;
    int siz;
    StackData(string id, int siz) {
        this->id = id;
        this->siz = siz;
    }
};

class Stack {
private:
    vector<StackData*> *_stack;
    int ebpPos;
public:
    Stack() { ebpPos = -1; _stack = new vector<StackData*>(); }
    void push(string, int);
    void pushFrame();
    void popFrame();
    int getStackOffset(string);
    int getBaseOffset(string);
    int getSizeOfVar(string);
    void printStack();
};

enum DataElementType {
    BYTE, WORD, ASCIIZ
};

struct DataElement {
    string code;
    DataElementType type;
};

string newString(string = "");
void newGlobal(string);
void newInt(string = "", int = 1);
void newChar(string = "", int = 1);
DataElementType getDataElementType(string);
int newTemp();
void freeTemp(int);
int newSaved();
void freeSaved(int);

int getSize(string, bool = false);

#endif