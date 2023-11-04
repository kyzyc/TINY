%{
#include "../globals.h"
#include "../util.h"
#include "../scan.h"
char tokenString[MAXTOKENLEN + 1];
%}
%option noyywrap

digit               [0-9]
number              {digit}+
letter              [a-zA-Z]
identifier          {letter}+
newline             \n
whitespace          [ \t]+

%%

"if"                     { return IF; }
"then"                   { return THEN; }
"else"                   { return ELSE; }
"end"                    { return END; }
"repeat"                 { return REPEAT; }
"until"                  { return UNTIL; }
"read"                   { return READ; }
"write"                  { return WRITE; }
":="                     { return ASSIGN; }
"="                      { return EQ; }
"<"                      { return LT; }
"+"                      { return PLUS; }
"-"                      { return MINUS; }
"*"                      { return TIMES; }
"/"                      { return OVER; }
"("                      { return LPAREN; }
")"                      { return RPAREN; }
";"                      { return SEMI; }
{number}                 { return NUM; }
{identifier}             { return ID; }
{newline}                { lineno++; }
{whitespace}             {  }
"{"                      {
                            char c;
                            do {
                                c = input();
                                if (c == '\n') lineno++;
                            } while (c != '}');
                         }

.                        { return ERROR; }
%%

TokenType getToken()
{
    static int firstTime = true;
    TokenType currentToken;
    if (firstTime) {
        firstTime = false;
        lineno++;
        yyin = source;
        yyout = listing;
    }
    currentToken = yylex();
    strncpy(tokenString, yytext, MAXTOKENLEN);
    if (TraceScan) {
        fprintf(listing, "\t%d: ", lineno);
        printToken(currentToken, tokenString);
    }
    return currentToken;
}
