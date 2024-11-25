/*
 * Copyright(c) 2020-2024 All rights reserved by Heekuck Oh.
 * 이 프로그램은 한양대학교 ERICA 컴퓨터학부 학생을 위한 교육용으로 제작되었다.
 */
#ifndef NODE_H
#define NODE_H

#include <stdbool.h>

/* 표현식 타입 정의 */
typedef enum {
    ASSIGN_EXPR,
    IF_EXPR,
    WHILE_EXPR,
    BLOCK_EXPR,
    LET_EXPR,
    CASE_EXPR,
    NEW_EXPR,
    ISVOID_EXPR,
    NOT_EXPR,
    OBJECT_EXPR,
    INT_EXPR,
    STRING_EXPR,
    BOOL_EXPR
} expr_type_t;

/* 표현식 구조체 */
typedef struct expr {
    expr_type_t type;
    union {
        struct { struct expr *condition, *then_branch, *else_branch; } if_expr;
        struct { struct expr *condition, *body; } while_expr;
        struct { struct expr_list *block_expr; } block_expr;
        struct { char *id; struct expr *expr; } assign_expr;
        struct { char *id; char *type; struct expr *init, *body; } let_expr;
        struct { struct expr *expr; struct case_list *cases; } case_expr;
        struct { struct expr *expr; } isvoid_expr;
        struct { struct expr *expr; } not_expr;
    };
    char *id;
    int int_value;
    char *string_value;
    bool bool_value;
} expr_t;

/* 표현식 리스트 구조체 */
typedef struct expr_list {
    expr_t *expr;
    struct expr_list *next;
} expr_list_t;

/* formal (매개변수) 구조체 */
typedef struct formal {
    char *name;
    char *type;
} formal_t;

/* formal 리스트 구조체 */
typedef struct formal_list {
    formal_t *formal;
    struct formal_list *next;
} formal_list_t;

/* feature 구조체 (메서드 또는 속성) */
typedef struct feature {
    char *name;
    char *type;
    formal_list_t *formals;
    expr_t *body;
} feature_t;

/* feature 리스트 구조체 */
typedef struct feature_list {
    feature_t *feature;
    struct feature_list *next;
} feature_list_t;

/* 클래스 구조체 */
typedef struct class {
    char *type;
    char *inherited;
    feature_list_t *features;
} class_t;

/* 클래스 리스트 구조체 */
typedef struct class_list {
    class_t *class;
    struct class_list *next;
} class_list_t;

/* case 구조체 */
typedef struct case_t {
    char *id;
    char *type;
    expr_t *expr;
} case_t;

/* case 리스트 구조체 */
typedef struct case_list {
    struct case_t *case_expr;
    struct case_list *next;
} case_list_t;

/* 함수 프로토타입 선언 */
class_list_t *create_class_list(class_t *class);
class_list_t *append_class_list(class_list_t *list, class_t *class);
class_t *create_class(char *type, char *inherited, feature_list_t *features);

feature_list_t *create_feature_list(feature_t *feature);
feature_list_t *append_feature_list(feature_list_t *list, feature_t *feature);
feature_t *create_method(char *name, formal_list_t *formals, char *type, expr_t *body);
feature_t *create_attribute(char *name, char *type, expr_t *init);

formal_list_t *create_formal_list(formal_t *formal);
formal_list_t *append_formal_list(formal_list_t *list, formal_t *formal);
formal_t *create_formal(char *name, char *type);

expr_t *create_assign_expr(char *id, expr_t *expr);
expr_t *create_if_expr(expr_t *condition, expr_t *then_branch, expr_t *else_branch);
expr_t *create_while_expr(expr_t *condition, expr_t *body);
expr_t *create_block_expr(expr_list_t *block);
expr_t *create_let_expr(char *id, char *type, expr_t *init, expr_t *body);
expr_t *create_case_expr(expr_t *expr, case_list_t *cases);
expr_t *create_new_expr(char *type);
expr_t *create_isvoid_expr(expr_t *expr);
expr_t *create_not_expr(expr_t *expr);
expr_t *create_object_expr(char *id);
expr_t *create_int_expr(int value);
expr_t *create_string_expr(char *value);
expr_t *create_bool_expr(bool value);

case_list_t *create_case_list(case_t *new_case);
case_list_t *append_case_list(case_list_t *list, case_t *new_case);
case_t *create_case(char *id, char *type, expr_t *expr);

expr_list_t *create_expr_list(expr_t *expr);
expr_list_t *append_expr_list(expr_list_t *list, expr_t *expr);

void show_class_list(class_list_t *class_list);

#endif // NODE_H

