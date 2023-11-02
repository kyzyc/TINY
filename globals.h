#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

// MAXRESERVED = the number of reserved words
#define MAXRESERVED 8

typedef enum {
    // book-keeping tokens
    ENDFILE, ERROR,
    // reserved words
    IF, THEN, ELSE, END, REPEAT, UNTIL, READ, WRITE,
    // multicharacter tokens
    ID, NUM,
    // special symbols
    ASSIGN, EQ, LT, PLUS, MINUS, TIMES, OVER, LPAREN, RPAREN, SEMI
} TokenType;

extern FILE* source;   // source code text file
extern FILE* listing;  // listing output text file
extern FILE* code;     // code text file for TM simulator

extern int lineno;     // source line number for listing

/*******************************************************************/
/***************** Syntax tree for parsing *************************/
/*******************************************************************/

/* typedef enum { StmtK, ExpK } NodeKind; */
/* typedef enum { IfK, RepeatK, AssignK, ReadK, WriteK } StmtKind; */
/* typedef enum { OpK, ConstK, IdK } ExpKind; */

// ExpType is used for type checking
/* typedef enum {Void, Integer, Boolean} ExpType; */

/* #define MAXCHILDREN 3 */

/* typedef struct treeNode { */
/*     struct treeNode* child[MAXCHILDREN]; */
/*     struct treeNode* stdlib; */
/*     int lineno; */
/*     NodeKind NodeKind; */
/*     union { */
/*         StmtKind stmt; */
/*         ExpKind exp; */
/*     } kind; */
/*     union { */
/*         TokenType op; */
/*         int val; */
/*         char* name; */
/*     } attr; */
/*     ExpType type;  // for type checking of exps */
/* } TreeNode; */

/*******************************************************************/
/*****************     Flags for tracing   *************************/
/*******************************************************************/

/* EchoSource = true, causes the source program to be echoed
   to the listing file with line numbers during parsing */
extern int EchoSource;

/* TraceScan = true, causes token information to be printed
   to the listing file as each token is recognized by the
   scanner */
extern int TraceScan;

/* // Error = true, prevents further passes if an error occurs */
/* extern int Error; */

#endif  // !_GLOBALS_H_
