/*
 * Copyright(c) 2020-2024 All rights reserved by Heekuck Oh.
 * 이 프로그램은 한양대학교 ERICA 컴퓨터학부 학생을 위한 교육용으로 제작되었다.
 * 한양대학교 ERICA 학생이 아닌 자는 이 프로그램을 수정하거나 배포할 수 없다.
 * 프로그램을 수정할 경우 날짜, 학과, 학번, 이름, 수정 내용을 기록한다.
 */
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
DASHCOMMENT --.*\n

%%

"(*"           { BEGIN(COMMENT); }
<COMMENT>"*)"  { BEGIN(INITIAL); }
<COMMENT>.     /* Skip */;
<COMMENT>\n    /* Skip */;

{WHITESPACE}    /* SKIP */
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
    return INTEGER;
}

\"([^\"\n\\]|\\[btnf\"\\])*\" {
    /* 큰따옴표를 제외하고 문자열을 처리 */
    char *str = strdup(yytext + 1);  /* 처음 큰따옴표 제거하고 복사 */
    str[strlen(str) - 1] = '\0';  /* 마지막 큰따옴표 제거 */
    free(str);  /* 할당된 메모리 해제 */
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
.       { fprintf(stderr, "Skip unknown character %s in line %d\n", yytext, yylineno); }

%%

