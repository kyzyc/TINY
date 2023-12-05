#include <string.h>
#include <stdlib.h>
#include "globals.h"
#include "util.h"
#include "scan.h"
#include "parse.h"

#define NO_PARSE   false
#define NO_ANALYSE false
#define NO_CODE    false

size_t lineno = 1;

FILE* source;
FILE* listing;
FILE* code;

bool EchoSource = true;
bool TraceScan = false;
bool TraceParse = true;

bool Error = false;

int main(int argc, char *argv[]) {
    TreeNode* syntaxTree;
    char pgm[20];  // source code file name
    if (argc != 2) {
        fprintf(stderr, "usage: %s <filename>\n", argv[0]);
        exit(1);
    }
    strcpy(pgm, argv[1]);
    if (strstr(pgm, ".tny") == NULL) {
        strcat(pgm, ".tny");
    }
    source = fopen(pgm, "r");
    if (source == NULL) {
        fprintf(stderr, "File %s not found\n", pgm);
        exit(1);
    }
    listing = stdout;  // send listing to screen
    fprintf(listing, "\nTINY COMPILATION: %s\n", pgm);
    if (!initialTokenString()) {
        fprintf(stderr, "initial tokenString failed\n");
        exit(1);
    }
#if NO_PARSE
    while (getToken() != ENDFILE)
        ;
#else
    syntaxTree = parse();
    if (TraceParse) {
        fprintf(listing, "\nSyntax tree: \n");
        printTree(syntaxTree);
    }
    return 0;
#endif
}

