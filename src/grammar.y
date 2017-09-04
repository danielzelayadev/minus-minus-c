%{
    #include <stdio.h>
    
	int yylex();

	extern int yylineno, column;
	extern char *yytext;

	void yyerror(const char *str)
	{
		printf("[%d:%d] %s\n", yylineno, column, str);
	}

	#define YYERROR_VERBOSE 1
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


%start compilation_unit

%%

compilation_unit
	: compilation_unit global_declaration
	| global_declaration;

global_declaration
	: function_definition;

function_definition
	: function_prototype optional_function_body;

function_prototype
	: data_type ID '(' parameter_list ')';

data_type
	: var_type
	| KW_VOID;

var_type
	: KW_INT optional_pointer
	| KW_CHAR optional_pointer;

optional_pointer
	: '*'
	| %empty;

parameter_list
	: var_dec_list
	| %empty;

var_dec_list
	: var_dec_list ',' var_dec
	| var_dec;

var_dec
	: var_type ID;

optional_function_body
	: code_block
	| ';';

code_block
	: '{' statement_list '}';

statement_list
	: %empty;