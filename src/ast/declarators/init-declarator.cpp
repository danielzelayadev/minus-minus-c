#include "init-declarator.h"
#include "array-declarator.h"
#include "function-declarator.h"
#include "../expressions.h"
#include "../initializers.h"
#include "../../code-gen/memory.h"
#include "../../code-gen/helpers.h"
#include <iostream>

extern Stack *callStack;
extern int currScope;
extern string globalInits;

InitDeclarator::InitDeclarator(Declarator* decl, Initializer* init) {
    this->declarator  = decl;
    this->initializer = init;
}

string InitDeclarator::genCode(DataType dt) {
    string code;
    string id = declarator->id;
    ArrayDeclarator *arrDecl = dynamic_cast<ArrayDeclarator*>(declarator);

    if (dynamic_cast<FunctionDeclarator*>(declarator)) return "";

    if (arrDecl) {
        cout << "TODO: Support array declarations\n";
    } else {
        Expression *initExpr = initializer ? ((VarInitializer*)initializer)->expr : 0;

        if (!currScope)
            if (dt == INT)
                newInt(id);
            else
                newChar(id);
        else
            if (dt == INT)
                code += stackAlloc(4);
            else
                code += stackAlloc(1);
        
        callStack->push(id, dt == INT ? 4 : 1);

        if (initExpr) {
            if (currScope) {
                code += initExpr->genCode();
                code += sw(toRegStr(initExpr->place), callStack->getBaseOffset(id), "$fp");
            }
            else {
                int tmp = newTemp();
                string tmpStr = toRegStr(tmp);
                
                globalInits += initExpr->genCode();
                globalInits += la(tmpStr, id);
                globalInits += sw(toRegStr(initExpr->place), 0, tmpStr);

                freeTemp(tmp);
            }

            freeTemp(initExpr->place);
        }
    }

    return code;
}

void InitDeclarator::checkSemantic(DataType dt) {

}

string InitDeclarator::toString() {
    string str = declarator->toString();

    if (initializer) str += " = " + initializer->toString();

    return str;
}