#include "helpers.h"

int labelCount = 0;

string newLabel(string prefix) {
    return prefix + to_string(labelCount++) + ":\n\n";
}