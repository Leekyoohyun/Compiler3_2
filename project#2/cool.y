/*
 * Copyright(c) 2020-2024 All rights reserved by Heekuck Oh.
 * 이 프로그램은 한양대학교 ERICA 컴퓨터학부 학생을 위한 교육용으로 제작되었다.
 * 한양대학교 ERICA 학생이 아닌 자는 이 프로그램을 수정하거나 배포할 수 없다.
 * 프로그램을 수정할 경우 날짜, 학과, 학번, 이름, 수정 내용을 기록한다.
 * 응용물리학과 2022066017 이규현
 */
%{
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "node.h"

int yylex();
extern FILE* yyin;
extern int yylineno;
extern char *yytext;
static int num_errors = 0;
static class_list_t *program;
void yyerror(char const *s);
%}

%union {
    class_t *class;
    class_list_t *class_list;
    feature_list_t *feature_list;
    feature_t *feature;
    formal_list_t *formal_list;
    formal_t *formal;
    expr_t *expr;
    expr_list_t *expr_list;
    case_list_t *case_list;
    char *s;
    int i;
    bool b;
}

%token CLASS INHERITS IF THEN ELSE FI LET IN
%token WHILE LOOP POOL CASE OF DARROW ESAC
%token NEW ISVOID ASSIGN NOT LTE
%token <s> STRING TYPE ID
%token <i> INTEGER
%token <b> BOOLEAN TRUE FALSE

%type <class> class
%type <class_list> class_list
%type <feature_list> feature_list
%type <feature> feature
%type <formal_list> formal_list
%type <formal> formal
%type <expr> expr
%type <expr_list> expr_list
%type <case_list> case_list

%start program

%%

program: class_list { program = $1; }
    ;

class_list: class_list class { $$ = append_class_list($1, $2); }
          | class { $$ = create_class_list($1); }
          | error ';' {
                yyerror("Error in class definition, skipping.");
                yyerrok; // 에러 복구
                $$ = NULL;
          }
    ;

class: CLASS TYPE '{' feature_list '}' ';'
    { $$ = create_class($2, NULL, $4); }
    | CLASS TYPE INHERITS TYPE '{' feature_list '}' ';'
    { $$ = create_class($2, $4, $6); }

    ;

feature_list: feature_list feature { $$ = append_feature_list($1, $2); }
            | /* empty */ { $$ = NULL; }
            ;

feature: ID '(' formal_list ')' ':' TYPE '{' expr '}'
    { $$ = create_method($1, $3, $6, $8); }
    | ID ':' TYPE
    { $$ = create_attribute($1, $3, NULL); }
    | ID ':' TYPE ASSIGN expr
    { $$ = create_attribute($1, $3, $5); }
    ;

formal_list: formal_list ',' formal { $$ = append_formal_list($1, $3); }
           | formal { $$ = create_formal_list($1); }
           | /* empty */ { $$ = NULL; }
    ;

formal: ID ':' TYPE { $$ = create_formal($1, $3); }
    ;

expr: ID ASSIGN expr { $$ = create_assign_expr($1, $3); }
    | IF expr THEN expr ELSE expr FI { $$ = create_if_expr($2, $4, $6); }
    | WHILE expr LOOP expr POOL { $$ = create_while_expr($2, $4); }
    | '{' expr_list '}' { $$ = create_block_expr($2); }
    | LET ID ':' TYPE IN expr
    { $$ = create_let_expr($2, $4, NULL, $6); }
    | LET ID ':' TYPE ASSIGN expr IN expr
    { $$ = create_let_expr($2, $4, $6, $8); }
    | CASE expr OF case_list ESAC { $$ = create_case_expr($2, $4); }
    | NEW TYPE { $$ = create_new_expr($2); }
    | ISVOID expr { $$ = create_isvoid_expr($2); }
    | NOT expr { $$ = create_not_expr($2); }
    | '(' expr ')' { $$ = $2; }
    | ID { $$ = create_object_expr($1); }
    | INTEGER { $$ = create_int_expr($1); }
    | STRING { $$ = create_string_expr($1); }
    | TRUE { $$ = create_bool_expr(true); }
    | FALSE { $$ = create_bool_expr(false); }
    ;

expr_list: expr_list ';' expr { $$ = append_expr_list($1, $3); }
         | expr { $$ = create_expr_list($1); }
         | /* empty */ { $$ = NULL; }
    ;

case_list: case_list ID ':' TYPE DARROW expr ';'
    { $$ = append_case_list($1, create_case($2, $4, $6)); }
         | ID ':' TYPE DARROW expr ';'
    { $$ = create_case_list(create_case($1, $3, $5)); }
    ;

%%

void yyerror(char const *s)
{
    /*
     * 오류의 개수를 누적한다.
     */
    ++num_errors;
    /*
     * 문법 오류가 발생한 줄번호와 관련된 토큰을 출력한다.
     */
    if (yychar > 0)
        printf("%s in line %d at \"%s\"\n", s, yylineno, yytext);
    else
        printf("%s in line %d (unexpected EOF)\n", s, yylineno);
}

int main(int argc, char *argv[])
{
    /*
     * 스캔할 COOL 파일을 연다. 파일명이 없으면 표준입력이 사용된다.
     */
    if (argc > 1)
        if (!(yyin = fopen(argv[1],"r"))) {
            printf("\"%s\"는 잘못된 파일 경로입니다.\n", argv[1]);
            exit(1);
        }
    /*
     * 구문분석을 위해 수행한다.
     */
    yyparse();
    /*
     * 오류의 개수를 출력한다.
     */
    if (num_errors > 0)
         printf("%d error(s) found\n", num_errors);
    else
         show_class_list(program);

    return 0;
}