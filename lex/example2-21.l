%{
/* a lex program that changes all numbers
   from decimal to hexadecimal notation,
   printing a summary statistic to stderr
*/
#include <stdlib.h>
#include <stdio.h>
int count = 0;
%}
%option noyywrap
digit [0-9]
number {digit}+
%%
{number} { int n = atoi(yytext);
           printf("%x", n);
           if (n > 9) count++; }
%%
int main()
{
    yylex();
    fprintf(stderr, "numebr of replacements = %d\n", count);
    return 0;
}
