/**
 * simple integer arithmetic calculator
 * according to the EBNF:
 * 
 * <exp> -> <term> { <addop> <term> }
 * <addop> -> + | -
 * <term> -> <factor> { <mulop> <factor> }
 * <mulop> -> *
 * <factor> -> ( <exp> ) | Number
 * 
 * inputs a line of text from stdin
 * outputs "error" or the result
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

char token;

int expr();
int term();
int factor();

void error() {
    fprintf(stderr, "Error\n");
    exit(EXIT_FAILURE);
}

void match(char expectedToken) {
    if (token == expectedToken) {
        token = getchar();
    }
    else 
        error();
}

int expr() {
    int temp = term();
    while (token == '+' || token == '-') {
        switch (token) {
            case '+':
                match('+');
                temp += term();
                break;
            case '-':
                match('-');
                temp -= term();
                break;
        }
    }
    return temp;
}

int term() {
    int temp = factor();
    while (token == '*') {
        match('*');
        temp *= factor();
    }
    return temp;
}

int factor() {
    int temp;
    if (token == '(') {
        match('(');
        temp = expr();
        match(')');
    } else if (isdigit(token)) {
        ungetc(token, stdin);
        scanf("%d", &temp);
        token = getchar();
    } else {
        error();
    }
    return temp;
}

int main() {
    int result;

    token = getchar();

    result = expr();
    if (token == '\n') {
        printf("Result = %d\n", result);
    } else {
        error();
    }

    return 0;
}