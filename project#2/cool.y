%{
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "node.h"

int yylex();
extern FILE *yyin;
extern int yylineno;
extern char *yytext;

static int num_errors = 0;
static class_list_t *program;

void yyerror(const char *s);
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

program:
    class_list {
        program = $1;
    }
    ;

class_list:
    class_list class {
        $$ = append_class_list($1, $2);
    }
    | class {
        $$ = create_class_list($1);
    }
    ;

class:
    CLASS TYPE '{' feature_list '}' ';' {
        $$ = create_class($2, NULL, $4);
    }
    | CLASS TYPE INHERITS TYPE '{' feature_list '}' ';' {
        $$ = create_class($2, $4, $6);
    }
    ;

feature_list:
    feature_list feature {
        $$ = append_feature_list($1, $2);
    }
    | /* empty */ {
        $$ = NULL;
    }
    ;

feature:
    ID '(' formal_list ')' ':' TYPE '{' expr '}' {
        $$ = create_method($1, $3, $6, $8);
    }
    | ID ':' TYPE {
        $$ = create_attribute($1, $3, NULL);
    }
    | ID ':' TYPE ASSIGN expr {
        $$ = create_attribute($1, $3, $5);
    }
    ;

formal_list:
    formal_list ',' formal {
        $$ = append_formal_list($1, $3);
    }
    | formal {
        $$ = create_formal_list($1);
    }
    | /* empty */ {
        $$ = NULL;
    }
    ;

formal:
    ID ':' TYPE {
        $$ = create_formal($1, $3);
    }
    ;

expr:
    ID ASSIGN expr {
        $$ = create_assign_expr($1, $3);
    }
    | IF expr THEN expr ELSE expr FI {
        $$ = create_if_expr($2, $4, $6);
    }
    | WHILE expr LOOP expr POOL {
        $$ = create_while_expr($2, $4);
    }
    | '{' expr_list '}' {
        $$ = create_block_expr($2);
    }
    | LET ID ':' TYPE IN expr {
        $$ = create_let_expr($2, $4, NULL, $6);
    }
    | LET ID ':' TYPE ASSIGN expr IN expr {
        $$ = create_let_expr($2, $4, $6, $8);
    }
    | CASE expr OF case_list ESAC {
        $$ = create_case_expr($2, $4);
    }
    | NEW TYPE {
        $$ = create_new_expr($2);
    }
    | ISVOID expr {
        $$ = create_isvoid_expr($2);
    }
    | NOT expr {
        $$ = create_not_expr($2);
    }
    | '(' expr ')' {
        $$ = $2;
    }
    | ID {
        $$ = create_object_expr($1);
    }
    | INTEGER {
        $$ = create_int_expr($1);
    }
    | STRING {
        $$ = create_string_expr($1);
    }
    | TRUE {
        $$ = create_bool_expr(true);
    }
    | FALSE {
        $$ = create_bool_expr(false);
    }
    ;

expr_list:
    expr_list ';' expr {
        $$ = append_expr_list($1, $3);
    }
    | expr {
        $$ = create_expr_list($1);
    }
    ;

case_list:
    case_list ID ':' TYPE DARROW expr ';' {
        $$ = append_case_list($1, create_case($2, $4, $6));
    }
    | ID ':' TYPE DARROW expr ';' {
        $$ = create_case_list(create_case($1, $3, $5));
    }
    ;


%%

void yyerror(const char *s) {
    ++num_errors;
    fprintf(stderr, "Syntax error at line %d near '%s': %s\n", yylineno, yytext, s);
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            fprintf(stderr, "Error: Cannot open file %s\n", argv[1]);
            exit(1);
        }
    }

    yyparse();

    if (num_errors == 0) {
        show_class_list(program);
    } else {
        fprintf(stderr, "%d error(s) found\n", num_errors);
    }

    return 0;
}
