%{
/* lex program to convert lowercase to 
   uppercase except inside comments
*/
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
%}
%option noyywrap
%%
[a-z] { putchar(toupper(yytext[0])); }
"/*" {
        char c;
        int done = false;
        ECHO;
        do {
            while ((c = input()) != '*') putchar(c);
            putchar(c);
            while ((c = input()) == '*') putchar(c);
            putchar(c);
            if (c == '/')
                done = true;
        } while(!done);
     }
%%
int main()
{
    yylex();
    return 0;
}
