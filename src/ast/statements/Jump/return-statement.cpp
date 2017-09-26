#include "return-statement.h"
#include "../../../code-gen/helpers.h"

string ReturnStatement::genCode() {
    return jr(expr);
}