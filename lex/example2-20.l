%{
/* a lex program that adds line numbers
   to lines of test, printing the new text
   to the standoard output
*/
#include <stdio.h>
int lineno = 1;
%}
%option noyywrap
line .*\n
%%
{line} { printf("%5d %s", lineno++, yytext); }
%%
int main() { yylex(); return 0; }
