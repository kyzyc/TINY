#ifndef _SCAN_H_
#define _SCAN_H_

#include "globals.h"

// maxinum size of a token
#define MAXTOKENLEN 40

// store the lexeme of each token (string value of token)
extern char tokenString[MAXTOKENLEN + 1];

// return the next token in source file
TokenType getToken();

#endif // !_SCAN_H_
