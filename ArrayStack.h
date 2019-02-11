//
// Created by IvanLu on 2019/1/29.
//

#ifndef CUTILITY_ARRAYSTACK_H
#define CUTILITY_ARRAYSTACK_H

#include "Stack.h"

typedef struct ARRAY_STACK {
    Stack parent;
    void **data;
    int top;
    int capacity;
} ArrayStack;

int ArrayStackEmpty(ArrayStack *v) {
    return v->top == 0;
}

void *ArrayStackTop(ArrayStack *v) {
    return v->data[v->top - 1];
}

int ArrayStackPush(ArrayStack *v, void *x) {
    if (v->top >= v->capacity) {
        fprintf(stderr, "Overflow\n");
        return 0;
    }
    v->data[v->top] = x;
    v->top++;
    return 1;
}

void *ArrayStackPop(ArrayStack *v) {
    void *x = NULL;
    if (v->top >= 0) {
        x = v->data[v->top - 1];
        v->top--;
    }
    return x;
}

void FreeArrayStack(ArrayStack *v) {
    int i;
    Object *object = NULL;
    for (i = 0; i < v->top; i++) {
        object = (Object *) (v->data[i]);
        if (object->free_self != NULL) {
            object->free_self(object);
        }
    }
    free(v->data);
    free(v);
}

ArrayStack *_InitArrayStack(int capacity) {
    ArrayStack *v;
    v = malloc(sizeof(ArrayStack));
    v->data = malloc(sizeof(void *) * capacity);
    v->top = 0;
    v->capacity = capacity;
    v->parent.top = (void *(*)(void *)) ArrayStackTop;
    v->parent.push = (int (*)(void *, void *)) ArrayStackPush;
    v->parent.pop = (void *(*)(void *)) ArrayStackPop;
    v->parent.empty = (int (*)(void *)) ArrayStackEmpty;
    v->parent.object.free_self = (void (*)(void *)) FreeArrayStack;
    return v;
}

#define InitArrayStack(arg0) _InitArrayStack(DEF_ARG(arg0,10))

#endif //CUTILITY_ARRAYSTACK_H
