#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum { START, COMMENTTRANSIATION, INSINCOMMENT, INMULTICOMMENT, LEAVEMULTICOMMENT, DONE } StateType;

typedef enum { COMMENT, OTHER, ENDFILE, ERROR } TokenType;

#define MAX_BUFFER_SIZE 256

static char line_buffer[MAX_BUFFER_SIZE];
static size_t buffer_pos = 0;
static size_t buffer_size = 0;

static FILE* source;
static FILE* listing;

static char getNextChar() {
    if (!(buffer_pos < buffer_size)) {
        if (fgets(line_buffer, MAX_BUFFER_SIZE - 1, source)) {
            buffer_size = strlen(line_buffer);
            buffer_pos = 0;
            return line_buffer[buffer_pos++];
        } else {
            return ENDFILE;
        }
    } else {
        return line_buffer[buffer_pos++];
        
    }
}

TokenType getToken() {
    StateType current_state = START;
    TokenType tokentype;

    while (current_state != DONE) {
        char c = getNextChar();
        switch (current_state) {
            case START:
                switch (c) {
                    case '/':
                        putchar(c);
                        current_state = COMMENTTRANSIATION;
                        break;
                    case ENDFILE:
                        tokentype = ENDFILE;
                        current_state = DONE;
                        break;
                    default:
                        putchar(c);
                        tokentype = OTHER;
                        current_state = DONE;
                        break;
                }
                break;
            case COMMENTTRANSIATION:
                switch (c) {
                    case '/':
                        putchar(c);
                        current_state = INSINCOMMENT;
                        break;
                    case '*':
                        putchar(c);
                        current_state = INMULTICOMMENT;
                        tokentype = OTHER;
                        break;
                    case ENDFILE:
                        tokentype = ENDFILE;
                        current_state = DONE;
                        break;
                    default:
                        putchar(c);
                        current_state = DONE;
                        break;
                }
                break;
            case INSINCOMMENT:
                switch (c) {
                    case '\n':
                        putchar(c);
                        current_state = DONE;
                        tokentype = COMMENT;
                        break;
                    case ENDFILE:
                        tokentype = COMMENT;
                        current_state = DONE;
                        break;
                    default:
                        putchar(toupper(c));
                        break;
                }
                break;
            case INMULTICOMMENT:
                switch (c) {
                    case '*':
                        putchar(c);
                        current_state = LEAVEMULTICOMMENT;
                        break;
                    case ENDFILE:
                        tokentype = ERROR;
                        current_state = DONE;
                        break;
                    default:
                        putchar(toupper(c));
                        break;
                }
                break;
            case LEAVEMULTICOMMENT:
                switch (c) {
                    case '*':
                        putchar(c);
                        break;
                    case '/':
                        putchar(c);
                        tokentype = COMMENT;
                        current_state = DONE;
                        break;
                    case ENDFILE:
                        tokentype = ERROR;
                        current_state = DONE;
                        break;
                    default:
                        putchar(toupper(c));
                        current_state = INMULTICOMMENT;
                        break;
                }
                break;
            case DONE:
                exit(EXIT_FAILURE);
        }
    }

    return tokentype;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "usage: ./exercises2-20 <filename>\n");
        exit(EXIT_FAILURE);
    }

    source = fopen(argv[1], "r");
    if (source == NULL) {
        fprintf(stderr, "cannot open source file %s!\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    listing = stdout;

    TokenType token;
    while ((token = getToken()) != ENDFILE) {
        if (token == ERROR) {
            fprintf(stderr, "Error occured!\n");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
