/*
 * Copyright(c) 2020-2024 All rights reserved by Heekuck Oh.
 * 이 프로그램은 한양대학교 ERICA 컴퓨터학부 학생을 위한 교육용으로 제작되었다.
 * 한양대학교 ERICA 학생이 아닌 자는 이 프로그램을 수정하거나 배포할 수 없다.
 * 프로그램을 수정할 경우 날짜, 학과, 학번, 이름, 수정 내용을 기록한다.
 *
 * 이규현 228
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 타입 정의
typedef struct Feature Feature;
typedef struct FeatureList FeatureList;
typedef struct Class Class;
typedef struct ClassList ClassList;
typedef struct Expr Expr;
typedef struct ExprList ExprList;
typedef struct Case Case;
typedef struct CaseList CaseList;

// 열거형 정의
typedef enum {
    EXPR_IF, EXPR_WHILE, EXPR_BLOCK, EXPR_INT, EXPR_STRING, EXPR_BOOL, EXPR_ID
} ExprType;

// 특성 정의
struct Feature {
    char *name;
    char *type;
    Expr *body;
};

struct FeatureList {
    Feature *feature;
    FeatureList *next;
};

// 클래스 정의
struct Class {
    char *type;
    char *inherited;
    FeatureList *features;
};

struct ClassList {
    Class *class;
    ClassList *next;
};

// 표현식 정의
struct Expr {
    ExprType type;
    union {
        struct {
            Expr *condition;
            Expr *then_branch;
            Expr *else_branch;
        } if_expr;
        struct {
            Expr *condition;
            Expr *body;
        } while_expr;
        struct {
            ExprList *block;
        } block_expr;
        int int_value;
        char *string_value;
        int bool_value;
        char *id;
    };
};

struct ExprList {
    Expr *expr;
    ExprList *next;
};

// Case 정의
struct Case {
    char *id;
    char *type;
    Expr *expr;
};

struct CaseList {
    Case *case_expr;
    CaseList *next;
};

// 함수 선언
ClassList *create_class_list(Class *class);
Class *create_class(char *type, char *inherited, FeatureList *features);
FeatureList *create_feature_list(Feature *feature);
Feature *create_feature(char *name, char *type, Expr *body);
Expr *create_expr_int(int value);
Expr *create_expr_string(char *value);
ExprList *create_expr_list(Expr *expr);

// 메모리 해제 함수
void free_class_list(ClassList *list);
void free_feature_list(FeatureList *list);
void free_expr_list(ExprList *list);

// 구현
ClassList *create_class_list(Class *class) {
    ClassList *list = malloc(sizeof(ClassList));
    if (!list) return NULL;
    list->class = class;
    list->next = NULL;
    return list;
}

Class *create_class(char *type, char *inherited, FeatureList *features) {
    Class *new_class = malloc(sizeof(Class));
    if (!new_class) return NULL;
    new_class->type = strdup(type);
    new_class->inherited = inherited ? strdup(inherited) : NULL;
    new_class->features = features;
    return new_class;
}

FeatureList *create_feature_list(Feature *feature) {
    FeatureList *list = malloc(sizeof(FeatureList));
    if (!list) return NULL;
    list->feature = feature;
    list->next = NULL;
    return list;
}

Feature *create_feature(char *name, char *type, Expr *body) {
    Feature *feature = malloc(sizeof(Feature));
    if (!feature) return NULL;
    feature->name = strdup(name);
    feature->type = strdup(type);
    feature->body = body;
    return feature;
}

Expr *create_expr_int(int value) {
    Expr *expr = malloc(sizeof(Expr));
    if (!expr) return NULL;
    expr->type = EXPR_INT;
    expr->int_value = value;
    return expr;
}

Expr *create_expr_string(char *value) {
    Expr *expr = malloc(sizeof(Expr));
    if (!expr) return NULL;
    expr->type = EXPR_STRING;
    expr->string_value = strdup(value);
    return expr;
}

ExprList *create_expr_list(Expr *expr) {
    ExprList *list = malloc(sizeof(ExprList));
    if (!list) return NULL;
    list->expr = expr;
    list->next = NULL;
    return list;
}

void free_class_list(ClassList *list) {
    while (list) {
        free(list->class->type);
        if (list->class->inherited) free(list->class->inherited);
        free_feature_list(list->class->features);
        free(list->class);
        ClassList *temp = list;
        list = list->next;
        free(temp);
    }
}

void free_feature_list(FeatureList *list) {
    while (list) {
        free(list->feature->name);
        free(list->feature->type);
        free(list->feature);
        FeatureList *temp = list;
        list = list->next;
        free(temp);
    }
}

void free_expr_list(ExprList *list) {
    while (list) {
        if (list->expr->type == EXPR_STRING) free(list->expr->string_value);
        free(list->expr);
        ExprList *temp = list;
        list = list->next;
        free(temp);
    }
}

// 메인 함수 예시
int main() {
    // 클래스 생성 예제
    Feature *feature = create_feature("age", "int", create_expr_int(25));
    FeatureList *feature_list = create_feature_list(feature);
    Class *class = create_class("Person", NULL, feature_list);
    ClassList *class_list = create_class_list(class);

    // 출력
    printf("Class: %s\n", class_list->class->type);
    printf("Feature: %s, Type: %s\n", feature->name, feature->type);

    // 메모리 해제
    free_class_list(class_list);

    return 0;
}

