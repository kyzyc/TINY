#ifndef _SCAN_H_
#define _SCAN_H_

#include "globals.h"

#define INITIALSIZE 8

// store the lexeme of each token (string value of token)
extern struct TokenString tokenString;

// initialize tokenString
bool initialTokenString();

// return the next token in source file
TokenType getToken();

#endif // !_SCAN_H_
