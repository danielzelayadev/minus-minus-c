%option noyywrap

%{
    #include <stdio.h>
    #include "tokens.h"
%}

%%

"char" { return KW_CHAR; }
"int"  { return KW_INT; }
"void" { return KW_VOID; }

"break"    { return KW_BREAK; }
"continue" { return KW_CONTINUE; }
"else"     { return KW_ELSE; }
"for"      { return KW_FOR; }
"if"       { return KW_IF; }
"return"   { return KW_RETURN; }
"while"    { return KW_WHILE; }

"sizeof" { return KW_SIZEOF; }


"++" { return OP_INCREMENT; }
"--" { return OP_DECREMENT; }
"!"  { return '!'; }

"+"  { return '+'; }
"-"  { return '-'; }

"*"  { return '*'; }
"/"  { return '/'; }
"%"  { return '%'; }

"="   { return '='; }
"+="  { return OP_PLUSEQ; }
"-="  { return OP_MINUSEQ; }
"*="  { return OP_TIMESEQ; }
"/="  { return OP_DIVEQ; }
"%="  { return OP_MODEQ; }
"&="  { return OP_ANDEQ; }
"|="  { return OP_OREQ; }
"^="  { return OP_XOREQ; }
">>=" { return OP_SRLEQ; }
"<<=" { return OP_SLLEQ; }

"==" { return OP_EQ; }
"!=" { return OP_NOTEQ; }

"&"  { return '&'; }
"|"  { return '|'; }
"^"  { return '^'; }
"~"  { return '~'; }
">>" { return OP_SRL; }
"<<" { return OP_SLL; }

"&&" { return OP_CAND; }
"||" { return OP_COR; }
"!"  { return '!'; }

">"  { return '>'; }
"<"  { return '<'; }
">=" { return OP_GEQ; }
"<=" { return OP_LEQ; }

"?" { return '?'; }


"("  { return '('; }
")"  { return ')'; }
"{"  { return '{'; }
"}"  { return '}'; }
"["  { return '['; }
"]"  { return ']'; }
","  { return ','; }
";"  { return ';'; }
":"  { return ':'; }

. { printf("Unknown.\n"); }
