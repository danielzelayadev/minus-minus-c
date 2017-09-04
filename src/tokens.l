%option noyywrap
%option yylineno

%{
    #include <stdio.h>
    #include "tokens.h"

    extern char *yytext;
    extern int yylineno;

    void count();
%}

DIGIT [0-9]
LETTER [a-zA-Z_]
IGNORE [ \n\t\v\f]

%%

"char" { count(); return KW_CHAR; }
"int"  { count(); return KW_INT; }
"void" { count(); return KW_VOID; }

"break"    { count(); return KW_BREAK; }
"continue" { count(); return KW_CONTINUE; }
"else"     { count(); return KW_ELSE; }
"for"      { count(); return KW_FOR; }
"if"       { count(); return KW_IF; }
"return"   { count(); return KW_RETURN; }
"while"    { count(); return KW_WHILE; }

"sizeof" { count(); return KW_SIZEOF; }


"++" { count(); return OP_INCREMENT; }
"--" { count(); return OP_DECREMENT; }
"!"  { count(); return '!'; }

"+"  { count(); return '+'; }
"-"  { count(); return '-'; }

"*"  { count(); return '*'; }
"/"  { count(); return '/'; }
"%"  { count(); return '%'; }

"="   { count(); return '='; }
"+="  { count(); return OP_PLUSEQ; }
"-="  { count(); return OP_MINUSEQ; }
"*="  { count(); return OP_TIMESEQ; }
"/="  { count(); return OP_DIVEQ; }
"%="  { count(); return OP_MODEQ; }
"&="  { count(); return OP_ANDEQ; }
"|="  { count(); return OP_OREQ; }
"^="  { count(); return OP_XOREQ; }
">>=" { count(); return OP_SRLEQ; }
"<<=" { count(); return OP_SLLEQ; }

"==" { count(); return OP_EQ; }
"!=" { count(); return OP_NOTEQ; }

"&"  { count(); return '&'; }
"|"  { count(); return '|'; }
"^"  { count(); return '^'; }
"~"  { count(); return '~'; }
">>" { count(); return OP_SRL; }
"<<" { count(); return OP_SLL; }

"&&" { count(); return OP_CAND; }
"||" { count(); return OP_COR; }
"!"  { count(); return '!'; }

">"  { count(); return '>'; }
"<"  { count(); return '<'; }
">=" { count(); return OP_GEQ; }
"<=" { count(); return OP_LEQ; }

"?" { count(); return '?'; }


{LETTER}({LETTER}|{DIGIT})* { printf("%s\n", yytext); }


"("  { count(); return '('; }
")"  { count(); return ')'; }
"{"  { count(); return '{'; }
"}"  { count(); return '}'; }
"["  { count(); return '['; }
"]"  { count(); return ']'; }
","  { count(); return ','; }
";"  { count(); return ';'; }
":"  { count(); return ':'; }


{IGNORE} { count(); }


. { printf("Unknown at Line %d: %s\n", yylineno, yytext); }

%%

int column = 0;

void count() {
    int i;

	for (i = 0; yytext[i]; i++)
		if (yytext[i] == '\n')
			column = 0;
		else if (yytext[i] == '\t')
			column += 8 - (column % 8);
		else
			column++;
}