#include "scan.h"
#include <string.h>
#include "globals.h"
#include "util.h"

// states in scanner DFA
typedef enum {
    START, INASSIGN, INCOMMENT, INNUM, INID, DONE
} StateType;

// lexeme of identifier or reserved word
char tokenString[MAXTOKENLEN + 1];

// length of the input buffer for source code lines
#define BUFLEN 256

static char lineBuf[BUFLEN];  // holds the current line
static size_t linepos = 0;    // current position in LineBuf
static size_t bufsize = 0;    // current size of buffer string

/* getNextChar fetches the next non-blank character
   from lineBuf, reading in a new line if lineBuf is exhausted */
static char getNextChar(void) {
    if (!(linepos < bufsize)) {
        lineno++;
        if (fgets(lineBuf, BUFLEN - 1, source)) {
            if (EchoSource) {
                fprintf(listing, "%4zu: %s", lineno, lineBuf);
            }
            bufsize = strlen(lineBuf);
            linepos = 0;
            return lineBuf[linepos++];
        } else {
            return EOF;
        }
    } else {
        return lineBuf[linepos++];
    }
}

// ungetNextChar backtracks one character in lineBuf
static void ungetNextChar(void)
{
    linepos--;
}

// lookup table of reserved words
static struct {
    char* str;
    TokenType tok;
} reservedWords[MAXRESERVED] = {{"else", ELSE},     {"end", END},   {"if", IF},       {"read", READ},
                                {"repeat", REPEAT}, {"then", THEN}, {"until", UNTIL}, {"write", WRITE}};

// loopup an identifier to see if it is a reserved word, uses linear search
static TokenType reservedLookup(char* s) {
    size_t lo, hi, mid;
    lo = 0;
    hi = MAXRESERVED - 1;
    while (lo <= hi) {
        mid = lo + ((hi - lo) >> 1);
        int result = strcmp(s, reservedWords[mid].str);
        if (!result) {
            return reservedWords[mid].tok;
        } else if (result > 0){
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }

    return ID;
}


/*******************************************************************/
/************ the primary function of the scanner ******************/
/*******************************************************************/

TokenType getToken() {
    size_t tokenStringIndex = 0;  // index for storing into tokenString
    TokenType currentToken;       // holds current token to be returned
    StateType state = START;      // current state - always begins at start
    bool save;                    // flag to indicate save to tokenString

    while (state != DONE) {
        char c = getNextChar();
        save = true;
        switch (state) {
            case START:
                if (isdigit(c)) {
                    state = INNUM;
                } else if (isalpha(c)) {
                    state = INID;
                } else if (c == ':') {
                    state = INASSIGN;
                } else if ((c == ' ' || (c == '\t') || (c == '\n'))) {
                    save = false;
                } else if (c == '{') {
                    save = false;
                    state = INCOMMENT;
                } else {
                    state = DONE;
                    switch (c) {
                        case EOF:
                            save = false;
                            currentToken = ENDFILE;
                            break;
                        case '=':
                            currentToken = EQ;
                            break;
                        case '<':
                            currentToken = LT;
                            break;
                        case '+':
                            currentToken = PLUS;
                            break;
                        case '-':
                            currentToken = MINUS;
                            break;
                        case '*':
                            currentToken = TIMES;
                            break;
                        case '/':
                            currentToken = OVER;
                            break;
                        case '(':
                            currentToken = LPAREN;
                            break;
                        case ')':
                            currentToken = RPAREN;
                            break;
                        case ';':
                            currentToken = SEMI;
                            break;
                        default:
                            currentToken = ERROR;
                            break;
                    }
                }
                break;
            case INCOMMENT:
                save = false;
                if (c == '}') {
                    state = START;
                }
                break;
            case INASSIGN:
                state = DONE;
                if (c == '=') {
                    currentToken = ASSIGN;
                } else {
                    ungetNextChar();
                    save = false;
                    currentToken = ERROR;
                }
                break;
            case INNUM:
                if (!isdigit(c)) {
                    ungetNextChar();
                    save = false;
                    state = DONE;
                    currentToken = NUM;
                }
                break;
            case INID:
                if (!isalpha(c)) {
                    ungetNextChar();
                    save = false;
                    state = DONE;
                    currentToken = ID;
                }
                break;
            case DONE:
            default:
                fprintf(listing, "Scanner Bug: state = %d\n", state);
                state = DONE;
                currentToken = ERROR;
                break;
        }
        if ((save) && (tokenStringIndex <= MAXTOKENLEN)) {
            tokenString[tokenStringIndex++] = c;
        }
        if (state == DONE) {
            tokenString[tokenStringIndex] = '\0';
            if (currentToken == ID) {
                currentToken = reservedLookup(tokenString);
            }
        }
    }
    if (TraceScan) {
        fprintf(listing, "\t %zu: ", lineno);
        printToken(currentToken, tokenString);
    }
    return currentToken;
}
