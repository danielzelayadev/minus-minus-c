#include "helpers.h"

int labelCount = 0;

string newLabel(string prefix) {
    return prefix + to_string(labelCount++) + ":\n\n";
}

string stackIO(string instr, string reg, int offset) {
    return instr + " " + reg + ", " + to_string(offset) + "($sp)\n";
}

string stackAlloc(int howMuch) {
    return "addi $sp, $sp, -" + to_string(howMuch) + "\n";
}

string stackFree(int howMuch) {
    return "addi $sp, $sp, " + to_string(howMuch) + "\n";
}

string stackStoreW(string reg, int offset) {
    return stackIO("sw", reg, offset);
}

string stackStoreB(string reg, int offset) {
    return stackIO("sb", reg, offset);
}

string stackLoadW(string reg, int offset) {
    return stackIO("lw", reg, offset);
}

string stackLoadB(string reg, int offset) {
    return stackIO("lb", reg, offset);
}

string jumpReturn(Expression *expr) {
    string code;

    if (expr) {

    }

    return code + "jr $ra\n";
}