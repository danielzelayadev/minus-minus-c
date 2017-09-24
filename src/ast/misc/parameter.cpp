#include "parameter.h"
#include "../declarators.h"
#include "../../code-gen/helpers.h"

Parameter::Parameter(DataType dataType, Declarator *declarator) {
    this->dataType = dataType;
    this->declarator = declarator;
}

string Parameter::toString() {
    string str = mapType(dataType);

    if (declarator) str += " " + declarator->toString();

    return str;
}