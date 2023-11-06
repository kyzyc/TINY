%{
/* lex program to convert lowercase to 
   uppercase except inside comments
*/
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
bool inComment = false;
%}
%option noyywrap
%%
[a-z] { if (!inComment)
            putchar(toupper(yytext[0])); 
        else
            putchar(yytext[0]);
      }
"/*" {
        inComment = true;
        ECHO;
     }
"*/" {
        inComment = false;
        ECHO;
     }

%%
int main()
{
    yylex();
    return 0;
}
