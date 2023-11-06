%{
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
%}
%option noyywrap
%%
"/*" {
        char c;
        int done = false;
        ECHO;
        do {
            while ((c = input()) != '*') putchar(c);
            putchar(c);
            while ((c = input()) == '*') putchar(c);
            putchar(c);
            if (c == '/')
                done = true;
        } while(!done);
     }
"auto" { printf("AUTO");  }
"const" { printf("CONST");  }
"double" { printf("DOUBLE");  }
"float" { printf("FLOAT");  }
"int" { printf("INT");  }
"short" { printf("SHORT");  }
"struct" { printf("STRUCT");  }
"unsigned" { printf("UNSIGNED");  }
"break" { printf("BREAK");  }
"continue" { printf("CONTINUE");  }
"else" { printf("ELSE");  }
"for" { printf("FOR");  }
"long" { printf("LONG");  }
"signed" { printf("SIGNED");  }
"switch" { printf("SWITCH");  }
"void" { printf("VOID");  }
"case" { printf("CASE");  }
"default" { printf("DEFAULT");  }
"enum" { printf("ENUM");  }
"goto" { printf("GOTO");  }
"register" { printf("REGISTER");  }
"sizeof" { printf("SIZEOF");  }
"typedef" { printf("TYPEDEF");  }
"volatile" { printf("VOLATILE");  }
"char" { printf("CHAR");  }
"do" { printf("DO");  }
"extern" { printf("EXTERN");  }
"if" { printf("IF");  }
"return" { printf("RETURN");  }
"static" { printf("STATIC");  }
"union" { printf("UNION");  }
"while" { printf("WHILE");  }
%%
int main()
{
    yylex();
    return 0;
}
