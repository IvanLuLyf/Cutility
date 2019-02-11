//
// Created by IvanLu on 2019/1/20.
//

#ifndef CUTILITY_COMMON_H
#define CUTILITY_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define DEF_ARG(name, def_val) ((#name[0]) ? (name + 0) : def_val)

#define lambda(return_type, function_body) \
    ({ return_type fn function_body fn ;})

typedef struct OBJECT {
    void (*info)();

    char *str_ptr;

    char *(*toString)(void *);

    void (*free_self)(void *v);
} Object;

void Info(void *object) {
    ((Object *) object)->info();
}

char *parseString(void *object) {
    return ((Object *) object)->toString(object);
}

void Free(void *object) {
    ((Object *) object)->free_self(object);
}

typedef struct INTEGER {
    Object parent;
    int data;
} Integer;

char *IntToString(void *object) {
    if (((Integer *) object)->parent.str_ptr != NULL) {
        return ((Integer *) object)->parent.str_ptr;
    }
    int val = ((Integer *) object)->data;
    int tmp = val > 0 ? val : -val;
    int len = 0;
    while ((tmp = tmp / 10) > 0) {
        len++;
    }
    char *res = (char *) malloc(sizeof(char) * len + 2);
    sprintf(res, "%d", val);
    return res;
}

void FreeInteger(void *object) {
    if (((Integer *) object)->parent.str_ptr != NULL) {
        free(((Integer *) object)->parent.str_ptr);
    }
    free(object);
}

Integer *IntVal(int i) {
    Integer *data = (Integer *) malloc(sizeof(Integer));
    data->parent.str_ptr = NULL;
    data->parent.free_self = FreeInteger;
    data->parent.toString = IntToString;
    data->data = i;
    return data;
}

typedef struct LONG {
    Object parent;
    long data;
} Long;

char *LongToString(void *object) {
    if (((Long *) object)->parent.str_ptr != NULL) {
        return ((Long *) object)->parent.str_ptr;
    }
    long val = ((Long *) object)->data;
    long tmp = val > 0 ? val : -val;
    int len = 0;
    while ((tmp = tmp / 10) > 0) {
        len++;
    }
    char *res = (char *) malloc(sizeof(char) * len + 2);
    sprintf(res, "%ld", val);
    return res;
}

void FreeLong(void *object) {
    if (((Long *) object)->parent.str_ptr != NULL) {
        free(((Long *) object)->parent.str_ptr);
    }
    free(object);
}

Long *LongVal(long i) {
    Long *data = (Long *) malloc(sizeof(Long));
    data->parent.str_ptr = NULL;
    data->parent.free_self = FreeLong;
    data->parent.toString = LongToString;
    data->data = i;
    return data;
}

#endif //CUTILITY_COMMON_H
