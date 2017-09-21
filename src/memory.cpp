#include "memory.h"
#include "helpers.h"
#include <map>

map<string, string> data;

string newString(string literal) {
    string label = newLabel("str");

    data[label] = label + ": .asciiz \"" + literal + "\"";

    return label;
}