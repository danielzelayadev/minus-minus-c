#include "helpers.h"
#include "utils.h"

#define LABEL_HASH uniqueId(labelCount++, labelCount * 3, labelCount - 10, labelCount * 7)

int labelCount = 0;

string newLabel(string prefix) {
    return prefix + "__" + to_string(LABEL_HASH).substr(0, 3);
}

string move(string rdst, string rsrc) {
    return "move " + rdst + ", " + rsrc + "\n";
}

string clearScreen() {
    string code = "\n# screen setup\n";

    code += "li $a0, BRIGHT_WHITE\n";
    code += "li $a1, BLACK\n";
    code += "jal set_color\n";
    code += "jal clear_screen\n";

    return code;
}

string prologue() {
    string code = "\n# prologue\n";

    code += stackAlloc();
    code += sw("$fp", 0, "$sp");
    code += move("$fp", "$sp");

    return code + "\n";
}

string epilogue() {
    string code = "\n# epilogue\n";

    code += move("$sp", "$fp");
    code += sw("$fp", 0, "$sp");
    code += stackFree();

    return code + "\n";
}

string stackAlloc(int howMuch) {
    return "addi $sp, $sp, -" + to_string(howMuch) + "\n";
}

string stackFree(int howMuch) {
    return "addi $sp, $sp, " + to_string(howMuch) + "\n";
}

string la(string reg, string id) {
    return "la " + reg + ", " + id + "\n";
}

string io(string op, string src, int offset, string dst) {
    return op + " " + src + ", " + to_string(offset) + "(" + dst + ")\n";
}

string sw(string src, int offset, string dst) {
    return io("sw", src, offset, dst);
}

string sb(string src, int offset, string dst) {
    return io("sb", src, offset, dst);
}

string lw(string src, int offset, string dst) {
    return io("lw", src, offset, dst);
}

string lb(string src, int offset, string dst) {
    return io("lb", src, offset, dst);
}

string toRegStr(int i, char rt) {
    string str = "$";
    str.push_back(rt);
    return str + to_string(i);
}

string jumpReturn(Expression *expr) {
    string code;

    if (expr) {

    }

    return code + "jr $ra\n";
}