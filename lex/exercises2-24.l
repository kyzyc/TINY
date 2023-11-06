%{
#include <stdio.h>
int charcnt = 0;
int wordcnt = 0;
int linecnt = 0;
%}
%option noyywrap
char [a-zA-Z]
digit [0-9]
words {char}+{digit}*
newline \n
%%
{words} {
        charcnt += (strlen(yytext));
        wordcnt++;
      }
{newline} { charcnt++; linecnt++; }
.  { charcnt++; }

%%
int main()
{
    yylex();
    fprintf(stdout, "%d characters\n%d words\n%d lines\n", charcnt, wordcnt, linecnt);
    return 0;
}
