%{
    #include <stdio.h>
    
	int yylex();

	void yyerror(const char *str)
	{
		printf(str);
	}
%}

%%

input: %empty