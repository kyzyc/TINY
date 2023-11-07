#include <string.h>
#include <stdlib.h>
#include "globals.h"

#define NO_PARSE   true
#define NO_ANALYSE false
#define NO_CODE    false

#include "util.h"
#if NO_PARSE
#include "scan.h"
#else
#include "parse.h"
#endif
#if !NO_ANALYSE
#include "analyze.h"
#endif
#if !NO_CODE
#include "cgen.h"
#endif

size_t lineno = 1;
FILE* source;
FILE* listing;
FILE* code;

bool EchoSource = true;
bool TraceScan = true;

// int Error = false;

int main(int argc, char *argv[])
{
    char pgm[20];  // source code file name
    if (argc != 2) {
        fprintf(stderr, "usage: %s <filename>\n", argv[0]);
        exit(1);
    }
    strcpy(pgm, argv[1]);
    if (strchr(pgm, '.') == NULL) {
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
#endif
    return 0;
}

