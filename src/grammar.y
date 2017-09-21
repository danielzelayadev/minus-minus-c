%code requires {
	#include "unary-expr.h"
	#include "binary-expr.h"
	#include "postfix-expr.h"
	#include "primary-expr.h"
	#include "statements.h"
}

%{
    #include <stdio.h>
	#include "unary-expr.h"

	int yylex();

	CompilationUnit* ast;

	extern int yylineno, column;
	extern char *yytext;

	UnaryExpression *getUnaryInstance(int, Expression*);

	void yyerror(const char *str)
	{
		printf("[%d:%d] %s\n", yylineno, column, str);
	}

	#define YYERROR_VERBOSE 1
%}

%union {
	CompilationUnit* c_unit;
	GlobalDeclaration* gdec_t;

	vector<Declaration*>* decl_ls;

	Declarator* declr_t;

	InitDeclarator* ideclr_t;
	vector<InitDeclarator*>* ideclr_ls;

	Initializer* inlzr_t;

	Parameter* par_t;
	vector<Parameter*>* par_ls;

	DataType dt;
	UnaryOp  uo;

	Expression* expr_t;
	vector<Expression*>* expr_ls;

	Statement* stmt_t;
	vector<Statement*>* stmt_ls;

	char* char_ptr;
}

%type<c_unit>       compilation_unit
%type<gdec_t>       global_declaration function_definition declaration
%type<decl_ls>      declaration_list
%type<declr_t>      declarator direct_declarator
%type<dt>           data_type type_name
%type<uo>           unary_operator
%type<ideclr_ls>    init_declarator_list
%type<ideclr_t>     init_declarator
%type<inlzr_t>      initializer
%type<expr_ls>      initializer_list argument_list
%type<par_t>        parameter_declaration
%type<par_ls>       parameter_list
%type<expr_t>       expression constant_expression assignment_expression
%type<expr_t>       unary_expression cor_expression cand_expression conditional_expression 
%type<expr_t>       xor_expression or_expression and_expression equality_expression relational_expression 
%type<expr_t>       shift_expression additive_expression multiplicative_expression cast_expression
%type<expr_t>       postfix_expression primary_expression
%type<stmt_t>       statement code_block expression_statement selection_statement jump_statement iteration_statement
%type<stmt_ls>      statement_list
%type<char_ptr>     assignment_operator '='

%token KW_INT "int" KW_CHAR "char" KW_VOID "void"
%token KW_FOR "for" KW_WHILE "while" KW_IF "if" KW_ELSE "else"
%token KW_BREAK "break" KW_CONTINUE "continue" KW_RETURN "return"
%token KW_SIZEOF "sizeof"

%token OP_INCREMENT "++" OP_DECREMENT "--"
%token<char_ptr> OP_TIMESEQ "*=" OP_DIVEQ "/=" OP_MODEQ "%=" OP_ANDEQ "&=" OP_OREQ "|="
%token<char_ptr> OP_XOREQ "^=" OP_SRLEQ ">>=" OP_SLLEQ "<<=" OP_PLUSEQ "+=" OP_MINUSEQ "-="
%token OP_EQ "==" OP_NOTEQ "!=" OP_SRL ">>" OP_SLL "<<"
%token OP_CAND "&&" OP_COR "||" OP_GEQ "<=" OP_LEQ ">="

%token<char_ptr> ID "identifier" STRING_LIT "string literal"
%token<char_ptr> DEC_INT "int literal" HEX_INT "hexadecimal int literal" OCT_INT "octal int literal" 
%token<char_ptr> CHAR_LIT "char literal"


%start compilation_unit

%%

compilation_unit
	: compilation_unit global_declaration { $1->globalDecs->push_back($2); $$ = ast = $1; }
	| global_declaration { $$ = ast = new CompilationUnit(); $$->globalDecs->push_back($1); }
;

global_declaration
	: function_definition { $$ = $1; }
	| declaration { $$ = $1; }
;



function_definition
	: data_type declarator code_block { $$ = new FunctionDefinition($1, (FunctionDeclarator*)$2, (CodeBlock*)$3); }
	| declarator code_block { $$ = new FunctionDefinition((FunctionDeclarator*)$1, (CodeBlock*)$2); }
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
	| assignment_expression { $$ = new vector<Expression*>(); $$->push_back($1); }
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
	: data_type '*' { $$ = (DataType)($1 + 3); }
	| data_type { $$ = $1; }
;



argument_list
	: argument_list ',' expression { $1->push_back($3); $$ = $1; }
	| expression { $$ = new vector<Expression*>(); $$->push_back($1); }
;



unary_operator
	: '+' { $$ = IDENTITY; }
	| '-' { $$ = NUM_NEG; }
	| '*' { $$ = DEREF; }
	| '~' { $$ = BIT_COMPLEMENT; }
	| '&' { $$ = ADDRESSOF; }
	| '!' { $$ = LOG_NEG; }
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
	: assignment_expression { $$ = $1; }
;

constant_expression
	: conditional_expression { $$ = $1; }
;

assignment_expression
	: unary_expression assignment_operator assignment_expression { $$ = new AssignmentExpression($1, $3, $2); }
	| conditional_expression { $$ = $1; }
;

unary_expression
	: OP_INCREMENT unary_expression  { $$ = new PreIncrementExpression($2, PRE_INC); }
	| OP_DECREMENT unary_expression  { $$ = new PreDecrementExpression($2, PRE_DEC); }
	| unary_operator cast_expression { $$ = getUnaryInstance($1, $2); }
	| KW_SIZEOF unary_expression     { $$ = new SizeofExpression($2); }
	| KW_SIZEOF '(' type_name ')'    { $$ = new SizeofExpression($3); }
	| postfix_expression
;

postfix_expression
	: postfix_expression '[' expression ']'    { $$ = new ArrayAccess($1, $3); }
	| postfix_expression '(' ')'               { $$ = new FunctionCall($1, new vector<Expression*>()); }
	| postfix_expression '(' argument_list ')' { $$ = new FunctionCall($1, $3); }
	| postfix_expression OP_INCREMENT          { $$ = new PostIncrement($1); }
	| postfix_expression OP_DECREMENT          { $$ = new PostDecrement($1); }
	| primary_expression
;

primary_expression
	: ID                 { $$ = new IdExpression($1); }
	| DEC_INT            { $$ = new IntExpression(new string($1)); }
	| OCT_INT            { $$ = new IntExpression(new string($1)); }
	| HEX_INT            { $$ = new IntExpression(new string($1)); }
	| CHAR_LIT           { $$ = new CharExpression(new string($1)); }
	| STRING_LIT         { $$ = new StringExpression(new string($1)); }
	| '(' expression ')' { $$ = $2; }
;

conditional_expression
	: cor_expression '?' expression ':' conditional_expression { $$ = new ConditionalExpression($1, $3, $5); }
	| cor_expression
;

cor_expression
	: cor_expression OP_COR and_expression { $$ = new CondOrExpression($1, $3, "||"); }
	| cand_expression
;

cand_expression
	: cand_expression OP_CAND or_expression { $$ = new CondAndExpression($1, $3, "&&"); }
	| or_expression
;

or_expression
	: or_expression '|' xor_expression { $$ = new OrExpression($1, $3, "|"); }
	| xor_expression
;

xor_expression
	: xor_expression '^' and_expression { $$ = new XorExpression($1, $3, "^"); }
	| and_expression
;

and_expression
	: and_expression '&' equality_expression { $$ = new AndExpression($1, $3, "&"); }
	| equality_expression
;

equality_expression
	: equality_expression OP_EQ relational_expression    { $$ = new EqualsExpression($1, $3, "=="); }
	| equality_expression OP_NOTEQ relational_expression { $$ = new NotEqualsExpression($1, $3, "!="); }
	| relational_expression
;

relational_expression
	: relational_expression '>' shift_expression    { $$ = new GreaterThanExpression($1, $3, ">"); }
	| relational_expression '<' shift_expression    { $$ = new LessThanExpression($1, $3, "<"); }
	| relational_expression OP_GEQ shift_expression { $$ = new GteExpression($1, $3, ">="); }
	| relational_expression OP_LEQ shift_expression { $$ = new LteExpression($1, $3, "<="); }
	| shift_expression
;

shift_expression
	: shift_expression OP_SRL additive_expression { $$ = new ShiftRightExpression($1, $3, ">>"); }
	| shift_expression OP_SLL additive_expression { $$ = new ShiftLeftExpression($1, $3, "<<"); }
	| additive_expression
;

additive_expression
	: additive_expression '+' multiplicative_expression { $$ = new SumExpression($1, $3, "+"); }
	| additive_expression '-' multiplicative_expression { $$ = new SubExpression($1, $3, "-"); }
	| multiplicative_expression
;

multiplicative_expression
	: multiplicative_expression '*' cast_expression { $$ = new MulExpression($1, $3, "*"); }
	| multiplicative_expression '/' cast_expression { $$ = new DivExpression($1, $3, "/"); }
	| multiplicative_expression '%' cast_expression { $$ = new ModExpression($1, $3, "%"); }
	| cast_expression
;

cast_expression
	: '(' type_name ')' cast_expression { $$ = new CastExpression($2, $4); }
	| unary_expression
;



code_block
	: '{' declaration_list statement_list '}' { $$ = new CodeBlock($2, $3); }
;

declaration_list
	: declaration_list declaration { $1->push_back((Declaration*)$2); $$ = $1; }
	| %empty { $$ = new vector<Declaration*>(); }
;

statement_list
	: statement_list statement { $1->push_back($2); $$ = $1; }
	| %empty { $$ = new vector<Statement*>(); }
;

statement
	: code_block
	| expression_statement
	| selection_statement
	| iteration_statement
	| jump_statement
;

expression_statement
	: expression ';' { $$ = new ExpressionStatement($1); }
;

selection_statement
	: KW_IF '(' expression ')' statement { $$ = new IfStatement($3, $5); }
	| KW_IF '(' expression ')' statement KW_ELSE statement { $$ = new IfStatement($3, $5, $7); }
;

iteration_statement
	: KW_WHILE '(' expression ')' statement { $$ = new WhileStatement($3, $5); }
	| KW_FOR '(' expression_statement expression_statement ')' statement            { $$ = new ForStatement(((ExpressionStatement*)$3)->expr, ((ExpressionStatement*)$4)->expr, (Expression*)0, $6); }
	| KW_FOR '(' expression_statement expression_statement expression ')' statement { $$ = new ForStatement(((ExpressionStatement*)$3)->expr, ((ExpressionStatement*)$4)->expr, $5, $7); }
;

jump_statement
	: KW_CONTINUE ';'          { $$ = new ContinueStatement(); }
	| KW_BREAK ';'             { $$ = new BreakStatement(); }
	| KW_RETURN ';'            { $$ = new ReturnStatement(); }
	| KW_RETURN expression ';' { $$ = new ReturnStatement($2); }
;