#include "memory.h"
#include "helpers.h"
#include "../utils.h"
#include <iostream>
#include <stdlib.h>
#include <map>

#define NOREGS -1
#define TEMPCOUNT 10
#define SAVEDCOUNT 8

bool temps[TEMPCOUNT], saved[SAVEDCOUNT];
map<string, DataElement> data;

map<string, string> globals;

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

int Stack::getStackOffset(string id) {
    int offset = 0;

    if (ebpPos == -1) return -1;

    for (int i = _stack->size()-1; i >= 1; i--) {
        StackData *sd = (*_stack)[i];
        
        if (sd->id == id)
            return offset;

        offset += sd->siz;
    }

    return -1;
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

    DataElement de = { 
        label + ": .asciiz " + literal, 
        ASCIIZ 
    };

    data[label] = de;

    return label;
}

string genArray(int siz) {
    string arr;

    while (siz > 1) {
        arr += "0, ";
        siz--;
    }

    if (siz) arr += "0";

    return arr;
}

void newInt(string id, int howMany) {
    DataElement de = { 
        id + ": .word " + genArray(howMany), 
        WORD
    };
    data[id] = de;
}

void newChar(string id, int howMany) {
    DataElement de = { 
        id + ": .byte " + genArray(howMany), 
        BYTE 
    };
    data[id] = de;
}

DataElementType getDataElementType(string id) {
    return data[id].type;
}

int getFirstFreeTemp() {
    for (int i = 0; i < TEMPCOUNT; i++)
        if (!temps[i])
            return i;      
    return NOREGS;
}

int newTemp() {
    int freeTemp = getFirstFreeTemp();

    if (freeTemp == NOREGS) {
        cerr << "Whoops! Looks like we ran out of temporary registers X_X\n";
        exit(1);
    }

    temps[freeTemp] = true;

    return freeTemp;
}

void freeTemp(int i) {
    temps[i] = false;
}

int getFirstFreeSaved() {
    for (int i = 0; i < SAVEDCOUNT; i++)
        if (!saved[i])
            return i;      
    return NOREGS;
}

int newSaved() {
    int freeSaved = getFirstFreeSaved();

    if (freeSaved == NOREGS) {
        cerr << "Whoops! Looks like we ran out of saved registers X_X\n";
        exit(1);
    }

    saved[freeSaved] = true;

    return freeSaved;
}

void freeSaved(int i) {
    saved[i] = false;
}

void newGlobal(string name) {
    globals[name] = ".global " + name + "\n";
}