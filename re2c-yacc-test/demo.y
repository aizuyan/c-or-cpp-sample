%{
#include <stdio.h>
#include "demo_scanner.h"
extern int yylex(znode *zendlval);
void yyerror(char const *);
#define YYSTYPE znode
%}

%pure_parser

%token T_BEGIN
%token T_NUMBER
%token T_LOWER_CHAR
%token T_UPPER_CHAR	
%token T_EXIT
%token T_SLASH
%token T_BACK_SLASH
%token T_SEMICOLON
%token T_LEFT_BRACKETS
%token T_RIGHT_BRACKETS
%token T_QUOTES
%token T_DOUBLE_QUOTES
%token T_UNKNOWN
%token T_INPUT_ERROR
%token T_END
%token T_WHITESPACE

%%

begin: T_BEGIN {printf("token=%d: begin\n", $1.op_type);}
     | begin variable {
		printf("token=%d ", $2.op_type);
		if ($2.constant.value.str.len > 0) {
			printf("text=%s", $2.constant.value.str.val);
		}
		printf("\n");
}

variable: T_NUMBER {$$ = $1;}
|T_LOWER_CHAR {$$ = $1;}
|T_UPPER_CHAR {$$ = $1;}
|T_EXIT {$$ = $1;}
|T_SLASH {$$ = $1;}
|T_BACK_SLASH {$$ = $1;}
|T_QUOTES {$$ = $1;}
|T_DOUBLE_QUOTES {$$ = $1;}
|T_SEMICOLON {$$ = $1;}
|T_LEFT_BRACKETS {$$ = $1;}
|T_RIGHT_BRACKETS {$$ = $1;}
|T_UNKNOWN {$$ = $1;}
|T_INPUT_ERROR {$$ = $1;}
|T_END {$$ = $1;}
|T_WHITESPACE {$$ = $1;}

%%

void yyerror(char const *s) {
	printf("%s\n", s);	
}
