#include "memory.h"
#include "helpers.h"
#include "utils.h"
#include <iostream>
#include <stdlib.h>
#include <map>

#define NOTEMPS -1
#define TEMPCOUNT 10

bool temps[TEMPCOUNT];
map<string, string> data;

void Stack::push(string id, int siz) {
    _stack->push_back(new StackData(id, siz));
}

void Stack::pushFrame() {
    push(to_string(ebpPos), 4);
    ebpPos = _stack->size() - 1;
}

void Stack::popFrame() {
    StackData *sd;

    while (!isNumber((sd = _stack->back())->id)) {
        delete sd;
        _stack->pop_back();
    }

    ebpPos = atoi(sd->id.c_str());

    delete sd;
    _stack->pop_back();
}

int Stack::getBaseOffset(string id) {
    int offset = 4;

    if (ebpPos == -1) return 0;

    for (int i = ebpPos + 1; i < _stack->size(); i++) {
        StackData *sd = (*_stack)[i];
        
        if (sd->id == id)
            return offset * -1;

        offset += sd->siz;
    }

    offset = 4;

    for (int i = ebpPos - 1; i >=1; i--) {
        StackData *sd = (*_stack)[i];
        
        if (sd->id == id)
            return offset;
            
        offset += sd->siz;
    }

    return 0;
}

int Stack::getSizeOfVar(string id) {
    for (int i = _stack->size() - 1; i >= 1; i--) {
        StackData *sd = (*_stack)[i];
        if (sd->id == id)
            return sd->siz;
    }
    return -1;
}

string newString(string literal) {
    string label = newLabel("str");

    data[label] = label + ": .asciiz " + literal;

    return label;
}

void newInt(string id) {
    data[id] = id + ": .word 0";
}

void newChar(string id) {
    data[id] = id + ": .byte 0";
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