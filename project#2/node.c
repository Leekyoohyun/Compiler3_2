/*
 * Copyright(c) 2020-2024 All rights reserved by Heekuck Oh.
 * 이 프로그램은 한양대학교 ERICA 컴퓨터학부 학생을 위한 교육용으로 제작되었다.
 * 한양대학교 ERICA 학생이 아닌 자는 이 프로그램을 수정하거나 배포할 수 없다.
 * 이규현 11/24 7:43
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "node.h"

/* Helper function to safely duplicate a string */
char *strdup_safe(const char *src) {
    if (!src) return NULL;
    char *dup = malloc(strlen(src) + 1);
    if (!dup) return NULL;
    strcpy(dup, src);
    return dup;
}

case_t *create_case(char *id, char *type, expr_t *expr) {
    case_t *case_expr = malloc(sizeof(case_t));
    if (!case_expr) return NULL;
    case_expr->id = strdup_safe(id);
    case_expr->type = strdup_safe(type);
    case_expr->expr = expr;
    return case_expr;
}

expr_t *create_case_expr(expr_t *expr, case_list_t *cases) {
    expr_t *case_expr = malloc(sizeof(expr_t));
    if (!case_expr) return NULL;
    case_expr->type = CASE_EXPR;
    case_expr->block_expr.block_expr = (expr_list_t *)cases; // 적절히 연결
    return case_expr;
}

case_list_t *create_case_list(case_t *new_case) {
    case_list_t *list = malloc(sizeof(case_list_t));
    if (!list) return NULL;
    list->case_expr = new_case;
    list->next = NULL;
    return list;
}

expr_t *create_let_expr(char *id, char *type, expr_t *init, expr_t *body) {
    expr_t *let_expr = malloc(sizeof(expr_t));
    if (!let_expr) return NULL;
    let_expr->type = LET_EXPR;
    let_expr->id = strdup_safe(id);
    let_expr->string_value = strdup_safe(type);
    let_expr->int_value = (intptr_t)init;
    let_expr->bool_value = (intptr_t)body;
    return let_expr;
}



/* Class list functions */
class_list_t *create_class_list(class_t *class) {
    class_list_t *list = malloc(sizeof(class_list_t));
    if (!list) return NULL;
    list->class = class;
    list->next = NULL;
    return list;
}

class_list_t *append_class_list(class_list_t *list, class_t *class) {
    if (!list) return create_class_list(class);
    class_list_t *current = list;
    while (current->next) current = current->next;
    current->next = create_class_list(class);
    return list;
}

/* Class functions */
class_t *create_class(char *type, char *inherited, feature_list_t *features) {
    if (type && inherited && strcmp(type, inherited) == 0) {
        fprintf(stderr, "Error: Class %s cannot inherit itself.\n", type);
        return NULL;
    }
    class_t *new_class = malloc(sizeof(class_t));
    if (!new_class) return NULL;
    new_class->type = strdup_safe(type);
    new_class->inherited = inherited ? strdup_safe(inherited) : NULL;
    new_class->features = features;
    return new_class;
}


/* Feature list functions */
feature_list_t *create_feature_list(feature_t *feature) {
    feature_list_t *list = malloc(sizeof(feature_list_t));
    if (!list) return NULL;
    list->feature = feature;
    list->next = NULL;
    return list;
}

feature_list_t *append_feature_list(feature_list_t *list, feature_t *feature) {
    if (!list) return create_feature_list(feature);
    feature_list_t *current = list;
    while (current->next) current = current->next;
    current->next = create_feature_list(feature);
    return list;
}

/* Feature functions */
feature_t *create_method(char *name, formal_list_t *formals, char *type, expr_t *body) {
    feature_t *method = malloc(sizeof(feature_t));
    if (!method) return NULL;
    method->name = strdup_safe(name);
    method->type = strdup_safe(type);
    method->formals = formals;
    method->body = body;
    return method;
}

feature_t *create_attribute(char *name, char *type, expr_t *init) {
    feature_t *attribute = malloc(sizeof(feature_t));
    if (!attribute) return NULL;
    attribute->name = strdup_safe(name);
    attribute->type = strdup_safe(type);
    attribute->formals = NULL;
    attribute->body = init;
    return attribute;
}

case_list_t *append_case_list(case_list_t *list, case_t *new_case) {
    if (!list) return create_case_list(new_case);
    case_list_t *current = list;
    while (current->next) current = current->next;
    current->next = create_case_list(new_case);
    return list;
}

expr_t *create_int_expr(int value) {
    expr_t *expr = malloc(sizeof(expr_t));
    if (!expr) return NULL;
    expr->type = INT_EXPR;
    expr->int_value = value;
    return expr;
}

expr_t *create_isvoid_expr(expr_t *expr) {
    expr_t *isvoid_expr = malloc(sizeof(expr_t));
    if (!isvoid_expr) return NULL;
    isvoid_expr->type = ISVOID_EXPR;
    isvoid_expr->int_value = (intptr_t)expr;
    return isvoid_expr;
}

expr_t *create_new_expr(char *type) {
    expr_t *new_expr = malloc(sizeof(expr_t));
    if (!new_expr) return NULL;
    new_expr->type = NEW_EXPR;
    new_expr->string_value = strdup_safe(type);
    return new_expr;
}

expr_t *create_not_expr(expr_t *expr) {
    expr_t *not_expr = malloc(sizeof(expr_t));
    if (!not_expr) return NULL;
    not_expr->type = NOT_EXPR;
    not_expr->int_value = (intptr_t)expr;
    return not_expr;
}

expr_t *create_object_expr(char *id) {
    expr_t *object_expr = malloc(sizeof(expr_t));
    if (!object_expr) return NULL;
    object_expr->type = OBJECT_EXPR;
    object_expr->id = strdup_safe(id);
    return object_expr;
}

expr_t *create_string_expr(char *value) {
    expr_t *string_expr = malloc(sizeof(expr_t));
    if (!string_expr) return NULL;
    string_expr->type = STRING_EXPR;
    string_expr->string_value = strdup_safe(value);
    return string_expr;
}




/* Formal list functions */
formal_list_t *create_formal_list(formal_t *formal) {
    formal_list_t *list = malloc(sizeof(formal_list_t));
    if (!list) return NULL;
    list->formal = formal;
    list->next = NULL;
    return list;
}

formal_list_t *append_formal_list(formal_list_t *list, formal_t *formal) {
    if (!list) return create_formal_list(formal);
    formal_list_t *current = list;
    while (current->next) current = current->next;
    current->next = create_formal_list(formal);
    return list;
}

formal_t *create_formal(char *name, char *type) {
    formal_t *formal = malloc(sizeof(formal_t));
    if (!formal) return NULL;
    formal->name = strdup_safe(name);
    formal->type = strdup_safe(type);
    return formal;
}

/* Expression functions */
expr_t *create_assign_expr(char *id, expr_t *expr) {
    expr_t *assignment = malloc(sizeof(expr_t));
    if (!assignment) return NULL;
    assignment->type = ASSIGN_EXPR;
    assignment->id = strdup_safe(id);
    assignment->assign_expr.expr = expr; // assign_expr 필드 사용
    return assignment;
}


expr_t *create_if_expr(expr_t *condition, expr_t *then_branch, expr_t *else_branch) {
    expr_t *if_expr = malloc(sizeof(expr_t));
    if (!if_expr) return NULL;
    if_expr->type = IF_EXPR;
    if_expr->if_expr.condition = condition;
    if_expr->if_expr.then_branch = then_branch;
    if_expr->if_expr.else_branch = else_branch;
    return if_expr;
}

expr_t *create_while_expr(expr_t *condition, expr_t *body) {
    expr_t *while_expr = malloc(sizeof(expr_t));
    if (!while_expr) return NULL;
    while_expr->type = WHILE_EXPR;
    while_expr->while_expr.condition = condition;
    while_expr->while_expr.body = body;
    return while_expr;
}

expr_t *create_bool_expr(bool value) {
    expr_t *expr = malloc(sizeof(expr_t));
    if (!expr) return NULL;
    expr->type = BOOL_EXPR;
    expr->bool_value = value;
    return expr;
}


expr_t *create_block_expr(expr_list_t *block) {
    expr_t *block_expr = malloc(sizeof(expr_t));
    if (!block_expr) return NULL;
    block_expr->type = BLOCK_EXPR;
    block_expr->block_expr.block_expr = block;
    return block_expr;
}

/* Expression list functions */
expr_list_t *create_expr_list(expr_t *expr) {
    expr_list_t *list = malloc(sizeof(expr_list_t));
    if (!list) return NULL;
    list->expr = expr;
    list->next = NULL;
    return list;
}

expr_list_t *append_expr_list(expr_list_t *list, expr_t *expr) {
    if (!list) return create_expr_list(expr);
    expr_list_t *current = list;
    while (current->next) {
        if (current == current->next) { // 무한 루프 방지
            fprintf(stderr, "Error: Circular reference in expr_list detected.\n");
            return NULL;
        }
        current = current->next;
    }
    current->next = create_expr_list(expr);
    return list;
}



/* Memory cleanup functions */
void free_class_list(class_list_t *list) {
    while (list) {
        class_list_t *next = list->next;
        free(list->class->type);
        if (list->class->inherited) free(list->class->inherited);
        free_feature_list(list->class->features);
        free(list->class);
        free(list);
        list = next;
    }
}

void free_feature_list(feature_list_t *list) {
    while (list) {
        feature_list_t *next = list->next;
        free(list->feature->name);
        free(list->feature->type);
        if (list->feature->formals) free_formal_list(list->feature->formals);
        if (list->feature->body) free(list->feature->body);
        free(list->feature);
        free(list);
        list = next;
    }
}

void free_formal_list(formal_list_t *list) {
    while (list) {
        formal_list_t *next = list->next;
        free(list->formal->name);
        free(list->formal->type);
        free(list->formal);
        free(list);
        list = next;
    }
}

void free_expr_list(expr_list_t *list) {
    while (list) {
        expr_list_t *next = list->next;
        if (list->expr->type == STRING_EXPR) free(list->expr->string_value);
        free(list->expr);
        free(list);
        list = next;
    }
}

void show_class_list(class_list_t *class_list) {
    class_list_t *current = class_list;
    while (current) {
        if (current == current->next) { // 순환 참조 확인
            fprintf(stderr, "Error: Circular reference in class_list detected.\n");
            return;
        }
        printf("Class: %s\n", current->class->type);
        current = current->next;
    }
}

