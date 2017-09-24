#include "post-increment.h"
#include "../../../code-gen/memory.h"
#include "../../../code-gen/helpers.h"

string PostIncrement::genCode(bool preserve) {
    string code;
    int addrPlace, evalPlace, tmp;

    code += idExpr->genAddrCode();

    addrPlace = idExpr->place;

    code += idExpr->genCode();

    place = preserve ? newSaved() : idExpr->place;
    if (preserve) {
        code += stackPushReg(place, 's');
        code += move(toRegStr(place, 's'), toRegStr(idExpr->place));
        freeTemp(idExpr->place);
    }

    tmp = newTemp();

    code += addi(toRegStr(tmp), toRegStr(place), 1);
    code += sw(toRegStr(tmp), 0, toRegStr(addrPlace));

    freeTemp(tmp);
    freeTemp(addrPlace);

    return code;
}