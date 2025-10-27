%option noyywrap
%{
	qwerqwer
	qwerqwerqwr
	qwerqwerqwrerq
	wer
	qwerqwerqwrerqwer
	qwerqwerqwrerqw
%}
%arrayqwe
%x COMMENT
%S string
%s teop
%X qwerqwer
%p 100
%n 200
%a 300
%e 400
%k 500
%o 600
%p 100
%n 200
%a 300
%e 400
%k 500
%o 600
	#define BLANK a
a test
q' tre
_D9IGIT 	 [0-9]
%%
{_D9IGIT} printf("NUMBER: %s\n", yytext);
. printf("Invalid character: %c\n", *yytext);

%%

#include <stdio.h>
#include <locale.h>
#include <stdint.h>

int main()
{
	setlocale(LC_ALL, "");
	return (yylex());
}

