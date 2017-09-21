#include "memory.h"
#include "helpers.h"
#include <iostream>
#include <stdlib.h>
#include <map>

#define NOTEMPS -1
#define TEMPCOUNT 10

bool temps[TEMPCOUNT];
map<string, string> data;

string newString(string literal) {
    string label = newLabel("str");

    data[label] = label + ": .asciiz " + literal;

    return label;
}

int getFirstFreeTemp() {
    for (int i = 0; i < TEMPCOUNT; i++)
        if (!temps[i])
            return i;      
    return NOTEMPS;
}

int newTemp() {
    int freeTemp = getFirstFreeTemp();

    if (freeTemp == NOTEMPS) {
        cerr << "Whoops! Looks like we ran out of registers X_X\n";
        exit(1);
    }

    temps[freeTemp] = true;

    return freeTemp;
}

void freeTemp(int i) {
    temps[i] = false;
}