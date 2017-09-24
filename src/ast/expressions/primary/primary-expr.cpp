#include "primary-expr.h"
#include "../../../code-gen/helpers.h"

string TimeExpression::genCode(bool preserve) {
    string code;
    
    GET_PLACE()

    return code + "lw " + toRegStr(place, preserve ? 's' : 't') + ", MS_COUNTER_REG_ADDR\n";
}

string StringExpression::genCode(bool preserve) {
    string code;

    GET_PLACE()

    return code + la(toRegStr(place, preserve ? 's' : 't'), newString(*literal));
}

string IntExpression::genCode(bool preserve) {
    string code;

    GET_PLACE()
    
    return code + "li " + toRegStr(place, preserve ? 's' : 't') + ", " + *literal + "\n";
}

string CharExpression::genCode(bool preserve) {
    string code;

    GET_PLACE()
    
    return code + "li " + toRegStr(place, preserve ? 's' : 't') + ", " + *literal + "\n";
}