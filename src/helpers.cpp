#include "helpers.h"
#include "utils.h"

#define LABEL_HASH uniqueId(labelCount++, labelCount * 3, labelCount - 10, labelCount * 7)

int labelCount = 0;

string newLabel(string prefix) {
    return prefix + "__" + to_string(LABEL_HASH);
}

string move(string rdst, string rsrc) {
    return "move " + rdst + ", " + rsrc + "\n";
}

string clearScreen() {
    string code;

    code += "li $a0, BRIGHT_WHITE\n";
    code += "li $a1, BLACK\n";
    code += "jal set_color\n";
    code += "jal clear_screen\n";

    return code;
}

string prologue() {
    string code;

    code += stackAlloc();
    code += stackStoreW("$fp");
    code += move("$fp", "$sp");

    return code;
}

string epilogue() {
    string code;

    code += move("$sp", "$fp");
    code += stackLoadW("$fp");
    code += stackFree();

    return code;
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