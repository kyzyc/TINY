%{
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
%}
%option noyywrap
sin_comment "//"
%%
{sin_comment} {
                char c;
                ECHO;
                while ((c = input()) != '\n') {
                    putchar(toupper(c));
                }
                putchar(c);
              }

"/*" {
        char c;
        int done = false;
        ECHO;
        do {
            while ((c = input()) != '*') putchar(toupper(c));
            putchar(c);
            while ((c = input()) == '*') putchar(c);
            if (c == '/') {
                done = true;
                putchar(c);
            }
            else
                putchar(toupper(c));
        } while(!done);
     }
%%
int main()
{
    yylex();
    return 0;
}


