/* Generated by re2c 0.13.5 on Sat Apr 16 17:46:28 2016 */
#line 1 "demo_scanner.l"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "demo_scanner_def.h"
#include "demo_scanner.h"
#include "demo.tab.h"

/**
 * PHP源码中的字符串copy函数
 */
void *estrndup(void *ptr, int len){
	char *dst = malloc(len + 1);
	memcpy(dst, ptr, len);
	dst[len] = 0;
	return dst;
}

# define copy_value(zendlval, yytext,yyleng) \
	do{\
		zendlval->value.str.val = (char *) estrndup(yytext, yyleng); \
		zendlval->value.str.len = yyleng;\
	}while(0)
#define clear_value(zendlval) \
	do{\
		zendlval->value.str.val[0] = '\0';	\
		zendlval->value.str.len = 0; \
	}while(0)

Scanner scanner_globals;

#define YYCTYPE char
#define YYFILL(n) 
#define STATE(name)  yyc##name
#define BEGIN(state) YYSETCONDITION(STATE(state))
#define LANG_SCNG(v) (scanner_globals.v)
#define SCNG    LANG_SCNG

#define CLEAR_TOKEN() clear_value(zendlval);
#define SAVE_TOKEN() copy_value(zendlval, yytext, yyleng)	//	保存当前获取的字符串
#define YYGETCONDITION()  SCNG(yy_state)
#define YYSETCONDITION(s) SCNG(yy_state) = s
#define YYCURSOR  SCNG(yy_cursor)
#define YYLIMIT   SCNG(yy_limit)
#define YYMARKER  SCNG(yy_marker)
#define yytext       ((char*)SCNG(yy_text))
#define yyleng       SCNG(yy_leng)

/**
 * 搜索一个token
 */ 
int scan(zval *zendlval){
	SCNG(yy_text) = YYCURSOR;
	
#line 57 "demo_scanner.c"
{
	YYCTYPE yych;
	switch (YYGETCONDITION()) {
	case yycINITIAL: goto yyc_INITIAL;
	case yycST_IN_SCRIPTING: goto yyc_ST_IN_SCRIPTING;
	}
/* *********************************** */
yyc_INITIAL:

	if ((YYLIMIT - YYCURSOR) < 5) YYFILL(5);
	yych = *YYCURSOR;
	switch (yych) {
	case '<':	goto yy4;
	default:	goto yy2;
	}
yy2:
	++YYCURSOR;
yy3:
	{yyleng = YYCURSOR - SCNG(yy_text);}
#line 108 "demo_scanner.l"
	{return T_INPUT_ERROR;}
#line 79 "demo_scanner.c"
yy4:
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case '?':	goto yy5;
	default:	goto yy3;
	}
yy5:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'p':	goto yy7;
	default:	goto yy6;
	}
yy6:
	YYCURSOR = YYMARKER;
	goto yy3;
yy7:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'h':	goto yy8;
	default:	goto yy6;
	}
yy8:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'p':	goto yy9;
	default:	goto yy6;
	}
yy9:
	++YYCURSOR;
	{yyleng = YYCURSOR - SCNG(yy_text);}
#line 57 "demo_scanner.l"
	{BEGIN(ST_IN_SCRIPTING); return T_BEGIN;}
#line 112 "demo_scanner.c"
/* *********************************** */
yyc_ST_IN_SCRIPTING:
	if ((YYLIMIT - YYCURSOR) < 5) YYFILL(5);
	yych = *YYCURSOR;
	switch (yych) {
	case 0x00:	goto yy13;
	case '\t':
	case '\n':
	case '\r':
	case ' ':	goto yy17;
	case '"':	goto yy19;
	case '\'':	goto yy21;
	case '(':	goto yy23;
	case ')':	goto yy25;
	case '/':	goto yy27;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy29;
	case ';':	goto yy31;
	case '?':	goto yy33;
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':	goto yy34;
	case '\\':	goto yy36;
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy38;
	case 'e':	goto yy40;
	default:	goto yy15;
	}
yy13:
	++YYCURSOR;
	{yyleng = YYCURSOR - SCNG(yy_text);}
#line 101 "demo_scanner.l"
	{BEGIN(INITIAL); return T_END;}
#line 200 "demo_scanner.c"
yy15:
	++YYCURSOR;
yy16:
	{yyleng = YYCURSOR - SCNG(yy_text);}
#line 104 "demo_scanner.l"
	{
	  CLEAR_TOKEN();
	  return T_UNKNOWN;
	  }
#line 210 "demo_scanner.c"
yy17:
	++YYCURSOR;
	yych = *YYCURSOR;
	goto yy54;
yy18:
	{yyleng = YYCURSOR - SCNG(yy_text);}
#line 90 "demo_scanner.l"
	{return T_WHITESPACE;}
#line 219 "demo_scanner.c"
yy19:
	++YYCURSOR;
	{yyleng = YYCURSOR - SCNG(yy_text);}
#line 74 "demo_scanner.l"
	{
	  SAVE_TOKEN();
	  return T_DOUBLE_QUOTES;
	  }
#line 228 "demo_scanner.c"
yy21:
	++YYCURSOR;
	{yyleng = YYCURSOR - SCNG(yy_text);}
#line 70 "demo_scanner.l"
	{
	  SAVE_TOKEN();
	  return T_QUOTES;
	  }
#line 237 "demo_scanner.c"
yy23:
	++YYCURSOR;
	{yyleng = YYCURSOR - SCNG(yy_text);}
#line 62 "demo_scanner.l"
	{
	  SAVE_TOKEN();
	  return T_LEFT_BRACKETS;
	  }
#line 246 "demo_scanner.c"
yy25:
	++YYCURSOR;
	{yyleng = YYCURSOR - SCNG(yy_text);}
#line 66 "demo_scanner.l"
	{
	  SAVE_TOKEN();
	  return T_RIGHT_BRACKETS;
	  }
#line 255 "demo_scanner.c"
yy27:
	++YYCURSOR;
	{yyleng = YYCURSOR - SCNG(yy_text);}
#line 78 "demo_scanner.l"
	{
	  SAVE_TOKEN();
	  return T_SLASH;
	  }
#line 264 "demo_scanner.c"
yy29:
	++YYCURSOR;
	yych = *YYCURSOR;
	goto yy52;
yy30:
	{yyleng = YYCURSOR - SCNG(yy_text);}
#line 58 "demo_scanner.l"
	{
	  SAVE_TOKEN();
	  return T_NUMBER;
	  }
#line 276 "demo_scanner.c"
yy31:
	++YYCURSOR;
	{yyleng = YYCURSOR - SCNG(yy_text);}
#line 86 "demo_scanner.l"
	{
	  SAVE_TOKEN();
	  return T_SEMICOLON;
	  }
#line 285 "demo_scanner.c"
yy33:
	yych = *++YYCURSOR;
	switch (yych) {
	case '>':	goto yy49;
	default:	goto yy16;
	}
yy34:
	++YYCURSOR;
	yych = *YYCURSOR;
	goto yy48;
yy35:
	{yyleng = YYCURSOR - SCNG(yy_text);}
#line 96 "demo_scanner.l"
	{
	  SAVE_TOKEN();
	  return T_UPPER_CHAR;
	  }
#line 303 "demo_scanner.c"
yy36:
	++YYCURSOR;
	{yyleng = YYCURSOR - SCNG(yy_text);}
#line 82 "demo_scanner.l"
	{
	  SAVE_TOKEN();
	  return T_BACK_SLASH;
	  }
#line 312 "demo_scanner.c"
yy38:
	++YYCURSOR;
	yych = *YYCURSOR;
	goto yy42;
yy39:
	{yyleng = YYCURSOR - SCNG(yy_text);}
#line 92 "demo_scanner.l"
	{
	  SAVE_TOKEN();
	  return T_LOWER_CHAR;
	  }
#line 324 "demo_scanner.c"
yy40:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'x':	goto yy43;
	default:	goto yy42;
	}
yy41:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy42:
	switch (yych) {
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy41;
	default:	goto yy39;
	}
yy43:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'i':	goto yy44;
	default:	goto yy42;
	}
yy44:
	yych = *++YYCURSOR;
	switch (yych) {
	case 't':	goto yy45;
	default:	goto yy42;
	}
yy45:
	++YYCURSOR;
	switch ((yych = *YYCURSOR)) {
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy41;
	default:	goto yy46;
	}
yy46:
	{yyleng = YYCURSOR - SCNG(yy_text);}
#line 91 "demo_scanner.l"
	{ return T_EXIT; }
#line 412 "demo_scanner.c"
yy47:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy48:
	switch (yych) {
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':	goto yy47;
	default:	goto yy35;
	}
yy49:
	++YYCURSOR;
	{yyleng = YYCURSOR - SCNG(yy_text);}
#line 100 "demo_scanner.l"
	{BEGIN(INITIAL); return T_END;}
#line 452 "demo_scanner.c"
yy51:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy52:
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy51;
	default:	goto yy30;
	}
yy53:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy54:
	switch (yych) {
	case '\t':
	case '\n':
	case '\r':
	case ' ':	goto yy53;
	default:	goto yy18;
	}
}
#line 109 "demo_scanner.l"

}

/** 
 * bison执行中必须存在的yylex函数
 */
int yylex(znode *zendlval) {
	int token;

	while(token = scan(&zendlval->constant)) {
		zendlval->op_type = token;

		if (token == T_INPUT_ERROR) {
			printf("%s\n", "input error");
			break;
		}
		if (token == T_END) {
			printf("%s\n", "end");
			break;
		}
		return token;
	}
	return 0;


}
int main(int argc, char* argv[])
{
	BEGIN(INITIAL);	//	全局初始化，需要放在scan调用之前
	scanner_globals.yy_cursor = argv[1];	//将输入的第一个参数作为要解析的字符串

	yyparse();
	return 0;
}