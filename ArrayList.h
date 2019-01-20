//
// Created by IvanLu on 2019/1/20.
//

#ifndef CUTILITY_ARRAYLIST_H
#define CUTILITY_ARRAYLIST_H

#include "List.h"

typedef struct ARRAY_LIST {
    List parent;
    void **data;
    int length;
    int capacity;
} ArrayList;

void *ArrayListGet(ArrayList *v, int i) {
    return v->data[i];
}

int ArrayListLocate(ArrayList *v, void *x) {
    int i;
    for (i = 0; i < v->length; i++) {
        if (v->data[i] == x)
            return i;
    }
    return -1;
}

int ArrayListInsert(ArrayList *v, int pos, void *x) {
    int i;
    if (pos < 0 || pos > v->length) {
        fprintf(stderr, "Invalid Position\n");
        return 0;
    }
    if (v->length >= v->capacity) {
        fprintf(stderr, "Overflow\n");
        return 0;
    }
    for (i = v->length; i > pos; i--)
        v->data[i] = v->data[i - 1];
    v->data[pos] = x;
    v->length++;
    return 1;
}

int ArrayListInsertMany(ArrayList *v, int n, ...) {
    va_list ptr;
    int i = 0;
    if (v->length + n > v->capacity) {
        fprintf(stderr, "Overflow\n");
        return 0;
    }
    va_start(ptr, n);
    for (i = 0; i < n; i++) {
        v->data[v->length + i] = va_arg(ptr, void*);
    }
    v->length += n;
    va_end(ptr);
    return 1;
}

int ArrayListDelete(ArrayList *v, int pos) {
    int i;
    if (pos < 0 || pos > v->length) {
        fprintf(stderr, "Invalid Position\n");
        return 0;
    }
    for (i = pos; i < v->length; i++)
        v->data[i] = v->data[i + 1];
    v->length--;
    return 1;
}

void ArrayListForEach(ArrayList *v, void (*op)(void *)) {
    int i;
    for (i = 0; i < v->length; i++) {
        op(v->data[i]);
    }
}

void FreeArrayList(ArrayList *v) {
    free(v->data);
    free(v);
}

void ArrayListInfo() {
    printf("ArrayList\n");
}

char *ArrayListToString() {
    return "ArrayList";
}

ArrayList *_InitArrayList(int capacity) {
    ArrayList *v;
    v = malloc(sizeof(ArrayList));
    v->data = malloc(sizeof(void *) * capacity);
    v->length = 0;
    v->capacity = capacity;
    v->parent.insert = (int (*)(void *, int, void *)) ArrayListInsert;
    v->parent.delete = (int (*)(void *, int)) ArrayListDelete;
    v->parent.get = (void *(*)(void *, int)) ArrayListGet;
    v->parent.locate = (int (*)(void *, void *)) ArrayListLocate;
    v->parent.for_each = (void (*)(void *, void (*)(void *))) ArrayListForEach;
    v->parent.free_self = (void (*)(void *)) FreeArrayList;
    v->parent.object.info = ArrayListInfo;
    v->parent.object.toString = ArrayListToString;
    return v;
}

#define InitArrayList(arg0) _InitArrayList(DEF_ARG(arg0,10))

#endif //CUTILITY_ARRAYLIST_H
