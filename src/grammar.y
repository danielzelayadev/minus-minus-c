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
	| declaration
;



function_definition
	: data_type declarator code_block
	| declarator code_block
;



declaration
	: data_type ';'
	| data_type init_declarator_list ';'
;

init_declarator_list
	: init_declarator_list ',' init_declarator
	| init_declarator
;

init_declarator
	: declarator '=' initializer
	| declarator
;

declarator
	: '*' direct_declarator
	| direct_declarator
;

direct_declarator
	: ID '[' constant_expression ']'
	| ID '[' ']'
	| ID '(' parameter_list ')'
	| ID '(' ')'
	| ID
;

initializer
	: assignment_expression
	| '{' initializer_list '}'
	| '{' initializer_list ',' '}'
;

initializer_list
	: initializer_list ',' initializer
	| initializer
;

parameter_list
	: parameter_list ',' parameter_declaration
	| parameter_declaration
;

parameter_declaration
	: data_type declarator
	| data_type
;



data_type
	: KW_CHAR
	| KW_INT
	| KW_VOID
;

type_name
	: data_type '*'
	| data_type
;



argument_list
	: argument_list ',' expression
	| expression
;



unary_operator
	: '+'
	| '-'
	| '*'
	| '~'
	| '&'
	| '!'
;

assignment_operator
	: '='
	| OP_PLUSEQ
	| OP_MINUSEQ
	| OP_TIMESEQ
	| OP_DIVEQ
	| OP_MODEQ
	| OP_ANDEQ
	| OP_OREQ
	| OP_XOREQ
	| OP_SLLEQ
	| OP_SRLEQ
;



expression
	: assignment_expression
;

constant_expression
	: conditional_expression
;

assignment_expression
	: unary_expression assignment_operator assignment_expression
	| conditional_expression
;

unary_expression
	: OP_INCREMENT unary_expression
	| OP_DECREMENT unary_expression
	| unary_operator cast_expression
	| KW_SIZEOF unary_expression
	| KW_SIZEOF '(' type_name ')'
	| postfix_expression
;

postfix_expression
	: postfix_expression '[' expression ']'
	| postfix_expression '(' ')'
	| postfix_expression '(' argument_list ')'
	| postfix_expression OP_INCREMENT
	| postfix_expression OP_DECREMENT
	| primary_expression
;

primary_expression
	: ID
	| DEC_INT
	| OCT_INT
	| HEX_INT
	| CHAR_LIT
	| STRING_LIT
	| '(' expression ')'
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
	: '{' declaration_list statement_list '}'
;

declaration_list
	: declaration_list declaration
	| %empty
;

statement_list
	: statement_list statement
	| %empty
;

statement
	: code_block
	| expression_statement
	| selection_statement
	| iteration_statement
	| jump_statement
;

expression_statement
	: expression ';'
;

selection_statement
	: KW_IF '(' expression ')' statement
	| KW_IF '(' expression ')' statement KW_ELSE statement
;

iteration_statement
	: KW_WHILE '(' expression ')' statement
	| KW_FOR '(' expression_statement expression_statement ')' statement
	| KW_FOR '(' expression_statement expression_statement expression ')' statement
;

jump_statement
	: KW_CONTINUE ';'
	| KW_BREAK ';'
	| KW_RETURN ';'
	| KW_RETURN expression ';'
;