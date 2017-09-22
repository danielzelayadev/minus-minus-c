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
    int getBaseOffset(string);
};

string newString(string = "");
void newInt(string = "");
void newChar(string = "");
int newTemp();
void freeTemp(int);

#endif