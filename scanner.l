%option noyywrap
%{
	qwerqwer
	qwerqwerqwr
	qwerqwerqwrerq
	wer
	qwerqwerqwrerqwer
	qwerqwerqwrerqw
%}
te test
te test
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

