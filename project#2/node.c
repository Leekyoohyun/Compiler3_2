#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"

char *strdup_safe(const char *src) {
    if (!src) return NULL;
    char *dup = malloc(strlen(src) + 1);
    if (!dup) return NULL;
    strcpy(dup, src);
    return dup;
}

/* Class 관련 함수 */
class_list_t *create_class_list(class_t *class) {
    class_list_t *list = malloc(sizeof(class_list_t));
    if (!list) return NULL;
    list->class = class;
    list->next = NULL;
    return list;
}

//추가하는거
/* Append to expression list */
expr_list_t *append_expr_list(expr_list_t *list, expr_t *expr) {
    expr_list_t *node = malloc(sizeof(expr_list_t));
    if (!node) return NULL;
    node->expr = expr;
    node->next = NULL;
    if (!list) return node;
    expr_list_t *current = list;
    while (current->next) current = current->next;
    current->next = node;
    return list;
}

/* Append to formal list */
formal_list_t *append_formal_list(formal_list_t *list, formal_t *formal) {
    formal_list_t *node = malloc(sizeof(formal_list_t));
    if (!node) return NULL;
    node->formal = formal;
    node->next = NULL;
    if (!list) return node;
    formal_list_t *current = list;
    while (current->next) current = current->next;
    current->next = node;
    return list;
}



class_list_t *append_class_list(class_list_t *list, class_t *class) {
    if (!list) return create_class_list(class);
    class_list_t *current = list;
    while (current->next) current = current->next;
    current->next = create_class_list(class);
    return list;
}

class_t *create_class(char *type, char *inherited, feature_list_t *features) {
    class_t *new_class = malloc(sizeof(class_t));
    if (!new_class) return NULL;
    new_class->type = strdup_safe(type);
    new_class->inherited = inherited ? strdup_safe(inherited) : NULL;
    new_class->features = features;
    return new_class;
}

/* Feature 관련 함수 */
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

feature_t *create_method(char *name, formal_list_t *formals, char *type, expr_t *body) {
    feature_t *method = malloc(sizeof(feature_t));
    if (!method) return NULL;
    method->name = strdup_safe(name);
    method->type = strdup_safe(type);
    method->formals = formals;
    method->body = body;
    return method;
}

/* Create attribute */
feature_t *create_attribute(char *name, char *type, expr_t *init) {
    feature_t *attribute = malloc(sizeof(feature_t));
    if (!attribute) return NULL;
    attribute->name = strdup_safe(name);
    attribute->type = strdup_safe(type);
    attribute->formals = NULL;
    attribute->body = init;
    return attribute;
}

/* Formal 관련 함수 */
formal_list_t *create_formal_list(formal_t *formal) {
    formal_list_t *list = malloc(sizeof(formal_list_t));
    if (!list) return NULL;
    list->formal = formal;
    list->next = NULL;
    return list;
}

formal_t *create_formal(char *name, char *type) {
    formal_t *formal = malloc(sizeof(formal_t));
    if (!formal) return NULL;
    formal->name = strdup_safe(name);
    formal->type = strdup_safe(type);
    return formal;
}

/* Expression 관련 함수 */
expr_t *create_assign_expr(char *id, expr_t *expr) {
    expr_t *assignment = malloc(sizeof(expr_t));
    if (!assignment) return NULL;
    assignment->type = ASSIGN_EXPR;
    assignment->assign_expr.id = strdup_safe(id);
    assignment->assign_expr.expr = expr;
    return assignment;
}

/* Create block expression */
expr_t *create_block_expr(expr_list_t *block) {
    expr_t *expr = malloc(sizeof(expr_t));
    if (!expr) return NULL;
    expr->type = BLOCK_EXPR;
    expr->block_expr.block_expr = block;
    return expr;
}

/* Create boolean expression */
expr_t *create_bool_expr(bool value) {
    expr_t *expr = malloc(sizeof(expr_t));
    if (!expr) return NULL;
    expr->type = BOOL_EXPR;
    expr->bool_value = value;
    return expr;
}

/* Create case expression */
expr_t *create_case_expr(expr_t *expr, case_list_t *cases) {
    expr_t *case_expr = malloc(sizeof(expr_t));
    if (!case_expr) return NULL;
    case_expr->type = CASE_EXPR;
    case_expr->case_expr.expr = expr;  // 올바른 필드 접근
    case_expr->case_expr.cases = cases;
    return case_expr;
}


/* Case 관련 함수 */
case_list_t *append_case_list(case_list_t *list, case_t *new_case) {
    case_list_t *node = malloc(sizeof(case_list_t));
    if (!node) return NULL;
    node->case_expr = new_case;
    node->next = NULL;
    if (!list) return node;
    case_list_t *current = list;
    while (current->next) current = current->next;
    current->next = node;
    return list;
}

case_t *create_case(char *id, char *type, expr_t *expr) {
    case_t *new_case = malloc(sizeof(case_t));
    if (!new_case) return NULL;  // 메모리 할당 실패 시 NULL 반환
    new_case->id = strdup_safe(id);  // id 복사
    new_case->type = strdup_safe(type);  // type 복사
    new_case->expr = expr;  // 표현식 연결
    return new_case;
}


/* Create case list */
case_list_t *create_case_list(case_t *new_case) {
    case_list_t *list = malloc(sizeof(case_list_t));
    if (!list) return NULL;  // 메모리 할당 실패 시 NULL 반환
    list->case_expr = new_case;  // 새 케이스 추가
    list->next = NULL;  // 리스트 끝
    return list;
}


/* Create expression list */
expr_list_t *create_expr_list(expr_t *expr) {
    expr_list_t *list = malloc(sizeof(expr_list_t));
    if (!list) return NULL;
    list->expr = expr;
    list->next = NULL;
    return list;
}

/* Create if expression */
expr_t *create_if_expr(expr_t *condition, expr_t *then_branch, expr_t *else_branch) {
    expr_t *if_expr = malloc(sizeof(expr_t));
    if (!if_expr) return NULL;
    if_expr->type = IF_EXPR;
    if_expr->if_expr.condition = condition;
    if_expr->if_expr.then_branch = then_branch;
    if_expr->if_expr.else_branch = else_branch;
    return if_expr;
}

/* Create integer expression */
expr_t *create_int_expr(int value) {
    expr_t *expr = malloc(sizeof(expr_t));
    if (!expr) return NULL;
    expr->type = INT_EXPR;
    expr->int_value = value;
    return expr;
}

// ISVOID 표현식 생성 함수
expr_t *create_isvoid_expr(expr_t *expr) {
    expr_t *isvoid_expr = malloc(sizeof(expr_t));
    if (!isvoid_expr) return NULL;
    isvoid_expr->type = ISVOID_EXPR;
    isvoid_expr->isvoid_expr.expr = expr;  // 올바른 필드 접근
    return isvoid_expr;
}



/* Create let expression */
expr_t *create_let_expr(char *id, char *type, expr_t *init, expr_t *body) {
    expr_t *let_expr = malloc(sizeof(expr_t));
    if (!let_expr) return NULL;
    let_expr->type = LET_EXPR;
    let_expr->let_expr.id = strdup_safe(id);       // id 필드 복사
    let_expr->let_expr.type = strdup_safe(type);   // type 필드 복사
    let_expr->let_expr.init = init;               // 초기화 표현식
    let_expr->let_expr.body = body;               // 본문 표현식
    return let_expr;
}


/* Create new expression */
expr_t *create_new_expr(char *type) {
    expr_t *new_expr = malloc(sizeof(expr_t));
    if (!new_expr) return NULL;
    new_expr->type = NEW_EXPR;
    new_expr->string_value = strdup_safe(type);
    return new_expr;
}

// NOT 표현식 생성 함수
expr_t *create_not_expr(expr_t *expr) {
    expr_t *not_expr = malloc(sizeof(expr_t));
    if (!not_expr) return NULL;
    not_expr->type = NOT_EXPR;
    not_expr->not_expr.expr = expr;  // 올바른 필드 접근
    return not_expr;
}



/* Create object expression */
expr_t *create_object_expr(char *id) {
    expr_t *object_expr = malloc(sizeof(expr_t));
    if (!object_expr) return NULL;
    object_expr->type = OBJECT_EXPR;
    object_expr->id = strdup_safe(id);
    return object_expr;
}

/* Create string expression */
expr_t *create_string_expr(char *value) {
    expr_t *string_expr = malloc(sizeof(expr_t));
    if (!string_expr) return NULL;
    string_expr->type = STRING_EXPR;
    string_expr->string_value = strdup_safe(value);
    return string_expr;
}

/* Create while expression */
expr_t *create_while_expr(expr_t *condition, expr_t *body) {
    expr_t *while_expr = malloc(sizeof(expr_t));
    if (!while_expr) return NULL;
    while_expr->type = WHILE_EXPR;
    while_expr->while_expr.condition = condition;
    while_expr->while_expr.body = body;
    return while_expr;
}

/* Show class list */
void show_class_list(class_list_t *class_list) {
    while (class_list) {
        printf("Class: %s\n", class_list->class->type);
        class_list = class_list->next;
    }
}

/* 출력 및 메모리 관리 */
void free_case_list(case_list_t *list) {
    while (list) {
        case_list_t *next = list->next;
        free(list->case_expr->id);
        free(list->case_expr->type);
        free(list->case_expr);
        free(list);
        list = next;
    }
}
