#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef enum { START, INRESERVE, COMMENTTRANSIATION, INSINCOMMENT, INMULTICOMMENT, LEAVEMULTICOMMENT, DONE } StateType;

typedef enum { COMMENT, RESERVE, OTHER, ENDFILE, ERROR } TokenType;

#define MAX_BUFFER_SIZE 256
#define MAX_RESERVE_SIZE 256
#define MAXRESERVED 32

static char line_buffer[MAX_BUFFER_SIZE];
static size_t buffer_pos = 0;
static size_t buffer_size = 0;

static char reserve_buffer[MAX_RESERVE_SIZE + 1];

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

static struct {
    char* str;
} reserved[MAXRESERVED] = {
    {"auto"}, {"const"}, {"double"}, {"float"}, {"int"}, {"short"}, {"struct"}, {"unsigned"},
    {"break"}, {"continue"}, {"else"}, {"for"}, {"long"}, {"signed"}, {"switch"}, {"void"},
    {"case"}, {"default"}, {"enum"}, {"goto"}, {"register"}, {"sizeof"}, {"typedef"}, {"volatile"},
    {"char"}, {"do"}, {"extern"}, {"if"}, {"return"}, {"static"}, {"union"}, {"while"}
};

static void ungetNextChar() {
    buffer_pos--;
}

static bool reserveLookup() {
    // printf("buffer: %s\n", reserve_buffer);
    for (int i = 0; i < MAXRESERVED; ++i) {
        if (!strcmp(reserve_buffer, reserved[i].str)) {
            return true;
        }
    }
    return false;
}

TokenType getToken() {
    StateType current_state = START;
    TokenType tokentype;
    bool save = true;
    int reserveIndex = 0;

    while (current_state != DONE) {
        char c = getNextChar();
        switch (current_state) {
            case START:
                if (isalpha(c)) {
                    current_state = INRESERVE;
                } else {
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
                }
                break;
            case INRESERVE:
                if (c == ENDFILE) {
                    tokentype = OTHER;
                    current_state = DONE;
                    break;
                }
                if (!isalpha(c)) {
                    ungetNextChar(); 
                    save = false; 
                    current_state = DONE;
                    tokentype = RESERVE;
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
                        putchar(c);
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
                        putchar(c);
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
                        putchar(c);
                        current_state = INMULTICOMMENT;
                        break;
                }
                break;
            case DONE:
                exit(EXIT_FAILURE);
        }
        if (save && reserveIndex <= MAX_RESERVE_SIZE) {
            reserve_buffer[reserveIndex++] = c;
        } 
        if (current_state == DONE && tokentype == RESERVE) {
            reserve_buffer[reserveIndex] = '\0'; 
            if (reserveLookup()) {
                // print uppercase
                for (int i = 0; reserve_buffer[i]; ++i) {
                    putchar(toupper(reserve_buffer[i]));
                }
            } else {
                printf("%s", reserve_buffer);
            }
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
// int for 
/*while int for if else */
