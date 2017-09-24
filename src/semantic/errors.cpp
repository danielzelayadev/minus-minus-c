#include "errors.h"
#include <iostream>
#include <vector>

vector<string> errors;

bool finishedWithErrors() {
    return errors.size();
}

void printErrors() {
    for (int i = 0; i < errors.size(); i++)
        cout << "\e[31mError: " << errors[i] << endl;
}

void error(string err) {
    errors.push_back(err);
}