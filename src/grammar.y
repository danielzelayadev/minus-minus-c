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
	| global_declaration
;

global_declaration
	: function_definition
	| variable_declaration ';'
;



function_definition
	: function_prototype optional_function_body
;

function_prototype
	: data_type ID '(' optional_parameter_list ')'
;

optional_function_body
	: code_block
	| ';'
;

optional_parameter_list
	: parameter_list
	| %empty
;

parameter_list
	: parameter_list ',' data_type ID
	| data_type ID
;



variable_declaration
	: data_type declaration_list
	;

declaration_list
	: declaration_list ',' ID optional_initializer
	| ID
;

optional_initializer
	: initializer
	| %empty
;

initializer
	: '=' expression
;



data_type
	: KW_CHAR optional_pointer
	| KW_INT optional_pointer
	| KW_VOID optional_pointer
;

optional_pointer
	: '*'
	| %empty
;



expression
	: assignment_expression
;

assignment_expression
	: unary_expression assignment_operator assignment_expression
	| conditional_expression
;

conditional_expression
	: cor_expression '?' expression ':' conditional_expression
	| cor_expression
;

cor_expression
	: cor_expression OP_COR and_expression
	| cand_expression
;

cand_expression
	: cand_expression OP_CAND or_expression
	| or_expression
;

or_expression
	: or_expression '|' xor_expression
	| xor_expression
;

xor_expression
	: xor_expression '^' and_expression
	| and_expression
;

and_expression
	: and_expression '&' equality_expression
	| equality_expression
;

equality_expression
	: equality_expression OP_EQ relational_expression
	| equality_expression OP_NOTEQ relational_expression
	| relational_expression
;

relational_expression
	: relational_expression '>' shift_expression
	| relational_expression '<' shift_expression
	| relational_expression OP_GEQ shift_expression
	| relational_expression OP_LEQ shift_expression
	| shift_expression
;

shift_expression
	: shift_expression OP_SRL additive_expression
	| shift_expression OP_SLL additive_expression
	| additive_expression
;

additive_expression
	: additive_expression '+' multiplicative_expression
	| additive_expression '-' multiplicative_expression
	| multiplicative_expression
;

multiplicative_expression
	: multiplicative_expression '*' cast_expression
	| multiplicative_expression '/' cast_expression
	| multiplicative_expression '%' cast_expression
	| cast_expression
;

cast_expression
	: '(' type_name ')' cast_expression
	| unary_expression
;



code_block
	: '{' statement_list '}'
;

statement_list
	: %empty
;