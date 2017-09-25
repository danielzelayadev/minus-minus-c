#include "init-declarator.h"
#include "array-declarator.h"
#include "function-declarator.h"
#include "../expressions.h"
#include "../initializers.h"
#include "../../code-gen/memory.h"
#include "../../code-gen/helpers.h"
#include <iostream>
#include <stdlib.h>

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
         int dims;
        ArrayInitializer *arrInit = 0;
        
        if (arrDecl->dimExpr)
            dims = atoi(((IntExpression*)arrDecl->dimExpr)->literal->c_str());
        else {
            arrInit = ((ArrayInitializer*)initializer);
            dims = arrInit->exprList->size();
        }

        if (!currScope)
            if (dt == INT)
                newInt(id, dims);
            else
                newChar(id, dims);
        else
            if (dt == INT)
                code += allocIntArray(id, dims);
            else
                code += allocCharArray(id, dims);

        if (initializer) {
            arrInit = arrInit ? arrInit : ((ArrayInitializer*)initializer);
            vector<Expression*> *initExprs = arrInit->exprList;
            if (!currScope) {
                int baseAddr = newTemp();
                string baseStr = toRegStr(baseAddr);

                globalInits += "la " + baseStr + ", " + id + "\n";

                for (int i = 0; i < initExprs->size(); i++) {
                    int offset = i * (dt == INT ? 4 : 1);
                    Expression *expr = (*initExprs)[i];
                    globalInits += expr->genCode();

                    globalInits += sw(toRegStr(expr->place), offset, baseStr);

                    freeTemp(expr->place);
                }

                freeTemp(baseAddr);
            }
            else {
                int baseAddr;
                code += useSaved(&baseAddr);
                string baseStr = toRegStr(baseAddr, 's');

                code += lw(baseStr, callStack->getBaseOffset(id), "$fp");

                for (int i = 0; i < initExprs->size(); i++) {
                    int offset = i * (dt == INT ? 4 : 1);
                    Expression *expr = (*initExprs)[i];
                    code += expr->genCode();

                    code += sw(toRegStr(expr->place), offset, baseStr);

                    freeTemp(expr->place);
                }

                code += releaseSaved(baseAddr);
            }
        }
    } else {
        Expression *initExpr = initializer ? ((VarInitializer*)initializer)->expr : 0;

        if (!currScope)
            if (dt == INT)
                newInt(id);
            else
                newChar(id);
        else {
            if (dt == INT)
                code += stackAlloc(4);
            else
                code += stackAlloc(1);
                
            callStack->push(id, dt == INT ? 4 : 1);
        }

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