/*
 * Copyright(c) 2020-2024 All rights reserved by Heekuck Oh.
 * 이 프로그램은 한양대학교 ERICA 컴퓨터학부 학생을 위한 교육용으로 제작되었다.
 * 한양대학교 ERICA 학생이 아닌 자는 이 프로그램을 수정하거나 배포할 수 없다.
 * 프로그램을 수정할 경우 날짜, 학과, 학번, 이름, 수정 내용을 기록한다.
 */
#ifndef NODE_H
#define NODE_H

#include <stdbool.h>

/* 표현식 타입 정의 */
typedef enum {
    EXPR_IF,
    EXPR_WHILE,
    EXPR_BLOCK,
    EXPR_INT,
    EXPR_STRING,
    EXPR_BOOL,
    EXPR_ID,
    ASSIGN_EXPR,
    IF_EXPR,
    WHILE_EXPR,
    BLOCK_EXPR,
    CASE_EXPR,
    NEW_EXPR,
    ISVOID_EXPR,
    NOT_EXPR,
    OBJECT_EXPR,
    INT_EXPR,
    STRING_EXPR,
    BOOL_EXPR
} expr_type_t;

/* 표현식 구조체 정의 */
typedef struct expr {
    expr_type_t type;
    union {
        struct {                     // if 표현식
            struct expr *condition;
            struct expr *then_branch;
            struct expr *else_branch;
        } if_expr;
        struct {                     // while 표현식
            struct expr *condition;
            struct expr *body;
        } while_expr;
        struct {                     // block 표현식
            struct expr_list *block_expr;
        } block_expr;
        int int_value;               // 정수 값
        char *string_value;          // 문자열 값
        bool bool_value;             // boolean 값
        char *id;                    // 변수 이름
    };
} expr_t;

/* 표현식 리스트 구조체 */
typedef struct expr_list {
    expr_t *expr;
    struct expr_list *next;
} expr_list_t;

void free_expr_list(expr_list_t *list);

/* formal (매개변수) 구조체 */
typedef struct formal {
    char *name;                     // 매개변수 이름
    char *type;                     // 매개변수 타입
} formal_t;

/* formal 리스트 구조체 */
typedef struct formal_list {
    formal_t *formal;
    struct formal_list *next;
} formal_list_t;

/* feature 구조체 (메서드 or 속성) */
typedef struct feature {
    char *name;                     // 메서드 or 속성 이름
    char *type;                     // 반환 타입 or 데이터 타입
    formal_list_t *formals;         // 메서드의 매개변수 리스트 (속성일 경우 NULL)
    expr_t *body;                   // 메서드의 구현 (속성 초기화 표현식 포함 가능)
} feature_t;

/* feature 리스트 구조체 */
typedef struct feature_list {
    feature_t *feature;
    struct feature_list *next;
} feature_list_t;

void free_feature_list(feature_list_t *list);

/* 클래스 구조체 */
typedef struct class {
    char *type;                     // 클래스 이름
    char *inherited;                // 상속받는 클래스 이름 (없으면 NULL)
    feature_list_t *features;       // 클래스의 feature 리스트
} class_t;

/* 클래스 리스트 구조체 */
typedef struct class_list {
    class_t *class;
    struct class_list *next;
} class_list_t;

void free_class_list(class_list_t *list);

/* case 표현식 타입 정의 */
typedef enum {
    CASE_CONDITION,  // 조건에 맞는 분기
} case_type_t;

/* case 표현식 구조체 정의 */
typedef struct case_expr {
    case_type_t type;
    union {
        struct {                     // 조건이 만족하는 case
            expr_t *condition;        // 조건
            expr_t *body;             // 조건 만족 시 실행할 코드
        } case_expr;
    };
} case_expr_t;

/* 케이스 구조체 */
typedef struct case_t {
    char *id;       // case의 ID
    char *type;     // case의 타입
    expr_t *expr;   // case에서 실행할 표현식
} case_t;

/* case 표현식 리스트 구조체 */
typedef struct case_list {
    case_t *case_expr;
    struct case_list *next;
} case_list_t;

void free_case_list(case_list_t *list);

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

expr_t *create_expr_if(expr_t *condition, expr_t *then_branch, expr_t *else_branch);
expr_t *create_expr_while(expr_t *condition, expr_t *body);
expr_t *create_expr_block(expr_list_t *block_expr);
expr_t *create_expr_int(int value);
expr_t *create_expr_string(char *value);
expr_t *create_expr_bool(bool value);
expr_t *create_expr_id(char *id);

expr_list_t *create_expr_list(expr_t *expr);
expr_list_t *append_expr_list(expr_list_t *list, expr_t *expr);

// Function declarations for expression creation
expr_t *create_assign_expr(char *id, expr_t *expr);
expr_t *create_if_expr(expr_t *condition, expr_t *true_branch, expr_t *false_branch);
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

// Function declarations for case list management
/* case 관련 함수 프로토타입 */
case_list_t *append_case_list(case_list_t *list, case_t *new_case);
case_list_t *create_case_list(case_t *new_case);
case_t *create_case(char *id, char *type, expr_t *expr);

void show_class_list(class_list_t *class_list);
void print_expr(expr_t *expr);

#endif // NODE_H
