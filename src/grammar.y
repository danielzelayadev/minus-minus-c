%code requires {
	#include "ast.h"
}

%{
    #include <stdio.h>
	#include "ast.h"

	int yylex();

	CompilationUnit* ast;

	extern int yylineno, column;
	extern char *yytext;

	void yyerror(const char *str)
	{
		printf("[%d:%d] %s\n", yylineno, column, str);
	}

	#define YYERROR_VERBOSE 1
%}

%union {
	CompilationUnit* c_unit;
	GlobalDeclaration* gdec_t;

	Declarator* declr_t;

	InitDeclarator* ideclr_t;
	vector<InitDeclarator*>* ideclr_ls;

	Initializer* inlzr_t;
	vector<Initializer*>* inlzr_ls;

	Parameter* par_t;
	vector<Parameter*>* par_ls;

	DataType dt;

	int int_t;

	char char_t;
	char* char_ptr;
}

%type<c_unit>       compilation_unit
%type<gdec_t>       global_declaration function_definition declaration
%type<declr_t>      declarator direct_declarator
%type<dt>           data_type
%type<ideclr_ls>    init_declarator_list
%type<ideclr_t>     init_declarator
%type<inlzr_t>      initializer
%type<inlzr_ls>     initializer_list
%type<par_t>        parameter_declaration
%type<par_ls>       parameter_list

%token KW_INT "int" KW_CHAR "char" KW_VOID "void"
%token KW_FOR "for" KW_WHILE "while" KW_IF "if" KW_ELSE "else"
%token KW_BREAK "break" KW_CONTINUE "continue" KW_RETURN "return"
%token KW_SIZEOF "sizeof"

%token OP_INCREMENT "++" OP_DECREMENT "--" OP_PLUSEQ "+=" OP_MINUSEQ "-="
%token OP_TIMESEQ "*=" OP_DIVEQ "/=" OP_MODEQ "%=" OP_ANDEQ "&=" OP_OREQ "|="
%token OP_XOREQ "^=" OP_SRLEQ ">>=" OP_SLLEQ "<<="
%token OP_EQ "==" OP_NOTEQ "!=" OP_SRL ">>" OP_SLL "<<"
%token OP_CAND "&&" OP_COR "||" OP_GEQ "<=" OP_LEQ ">="

%token<char_ptr> ID "identifier" STRING_LIT "string literal"
%token<int_t> DEC_INT "int literal" HEX_INT "hexadecimal int literal" OCT_INT "octal int literal" 
%token<char_t> CHAR_LIT "char literal"


%start compilation_unit

%%

compilation_unit
	: compilation_unit global_declaration { $1->globalDecs->push_back($2); $$ = ast = $1; }
	| global_declaration { $$ = new CompilationUnit(); $$->globalDecs->push_back($1); }
;

global_declaration
	: function_definition { $$ = $1; }
	| declaration { $$ = $1; }
;



function_definition
	: data_type declarator code_block { $$ = new FunctionDefinition($1, (FunctionDeclarator*)$2, 0); }
	| declarator code_block { $$ = new FunctionDefinition((FunctionDeclarator*)$1, 0); }
;



declaration
	: data_type ';' { $$ = new Declaration($1); }
	| data_type init_declarator_list ';' { $$ = new Declaration($1, $2); }
;

init_declarator_list
	: init_declarator_list ',' init_declarator { $1->push_back($3); $$ = $1; }
	| init_declarator { $$ = new vector<InitDeclarator*>(); $$->push_back($1); }
;

init_declarator
	: declarator '=' initializer { $$ = new InitDeclarator($1, $3); }
	| declarator { $$ = new InitDeclarator($1, 0); }
;

declarator
	: '*' direct_declarator { $2->isPointer = true; $$ = (Declarator*)$2; }
	| direct_declarator { $$ = $1; }
;

direct_declarator
	: ID '[' constant_expression ']' { $$ = new ArrayDeclarator($1, $3); }
	| ID '[' ']' { $$ = new ArrayDeclarator($1, 0); }
	| ID '(' parameter_list ')' { $$ = new FunctionDeclarator($1, $3); }
	| ID '(' ')' { $$ = new FunctionDeclarator($1, new vector<Parameter*>()); }
	| ID { $$ = new Declarator($1); }
;

initializer
	: assignment_expression { $$ = new VarInitializer($1); }
	| '{' initializer_list '}' { $$ = new ArrayInitializer($2); }
	| '{' initializer_list ',' '}' { $$ = new ArrayInitializer($2); }
;

initializer_list
	: initializer_list ',' assignment_expression { $1->push_back($3); $$ = $1; }
	| assignment_expression { $$ = new vector<Initializer*>(); $$->push_back($1); }
;

parameter_list
	: parameter_list ',' parameter_declaration { $1->push_back($3); $$ = $1; }
	| parameter_declaration { $$ = new vector<Parameter*>(); $$->push_back($1); }
;

parameter_declaration
	: data_type declarator { $$ = new Parameter($1, $2); }
	| data_type { $$ = new Parameter($1, 0); }
;



data_type
	: KW_CHAR { $$ = CHAR; }
	| KW_INT  { $$ = INT; }
	| KW_VOID { $$ = VOID; }
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