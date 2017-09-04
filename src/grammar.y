%{
    #include <stdio.h>
    
	int yylex();

	void yyerror(const char *str)
	{
		printf(str);
	}
%}

%token KW_INT "int" KW_CHAR "char" KW_VOID "void"
%token KW_FOR "for" KW_WHILE "while" KW_IF "if" KW_ELSE "else"
%token KW_BREAK "break" KW_CONTINUE "continue" KW_RETURN "return"
%token KW_SIZEOF "sizeof"

%token OP_INCREMENT "++" OP_DECREMENT "--" OP_PLUSEQ "+=" OP_MINUSEQ "-="
%token OP_TIMESEQ "*=" OP_DIVEQ "/=" OP_MODEQ "%=" OP_ANDEQ "&=" OP_OREQ "|="
%token OP_XOREQ "^=" OP_SRLEQ ">>=" OP_SLLEQ "<<="
%token OP_EQ "==" OP_NOTEQ "!=" OP_SRL ">>" OP_SLL "<<"
%token OP_CAND "&&" OP_COR "||" OP_GEQ "<=" OP_LEQ ">="

%token ID "identifier" DEC_INT "int literal" HEX_INT "hexadecimal int literal"
%token OCT_INT "octal int literal" CHAR_LIT "char literal" STRING_LIT "string literal"


%%

input: %empty