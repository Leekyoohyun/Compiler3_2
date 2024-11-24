%option noinput nounput yylineno
%{
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "node.h"
#include "cool.tab.h"
%}

%x COMMENT
%x S_LINE_COMMENT

NEWLINE     (\r\n|\n)
WHITESPACE  [ \t]+
DASHCOMMENT --.*

%%

{WHITESPACE}    /* skip */
{NEWLINE}       /* skip */
{DASHCOMMENT}   /* skip */

(?i:class)           { return CLASS; }
(?i:inherits)        { return INHERITS; }

"If"          { return IF; }
"if"          { return IF; }
"then"        { return THEN; }
"ELSE"        { return ELSE; }
"else"        { return ELSE; }
"fi"          { return FI; }
"while"       { return WHILE; }
"loop"        { return LOOP; }
"pool"        { return POOL; }
"let"         { return LET; }
"in"          { return IN; }
"case"        { return CASE; }
"of"          { return OF; }
"esac"        { return ESAC; }
"new"         { return NEW; }
"isvoid"      { return ISVOID; }
"true"        { return TRUE; }
"false"       { return FALSE; }
"not"         { return NOT; }

[A-Z][a-zA-Z0-9_]* { return TYPE; }

[a-zA-Z_][a-zA-Z0-9_]*    {
    return ID;
}

[0-9]+    {
    yylval.i = atoi(yytext); /* 정수 값 처리 */
    return INTEGER;
}

\"([^\"\n\\]|\\[btnf\"\\])*\" {
    /* 큰따옴표를 제외하고 문자열을 처리 */
    char *str = strdup(yytext + 1);  /* 처음 큰따옴표 제거하고 복사 */
    str[strlen(str) - 1] = '\0';  /* 마지막 큰따옴표 제거 */
    yylval.s = str;  /* 처리된 문자열 저장 */
    return STRING;
}

"("     { return '('; }
")"     { return ')'; }
"{"     { return '{'; }
"}"     { return '}'; }
"<="    { return LTE; }
"<-"    { return ASSIGN; }
"<"     { return '<'; }
"=>"    { return DARROW; }
"="     { return '='; }
","     { return ','; }
";"     { return ';'; }
":"     { return ':'; }
"."     { return '.'; }
"+"     { return '+'; }
"-"     { return '-'; }
"*"     { return '*'; }
"/"     { return '/'; }
"~"     { return '~'; }
"@"     { return '@'; }

. {
    fprintf(stderr, "Skip unknown character '%s' in line %d\n", yytext, yylineno);
}
%%

