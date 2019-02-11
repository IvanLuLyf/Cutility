//
// Created by IvanLu on 2019/1/29.
//

#ifndef CUTILITY_STACK_H
#define CUTILITY_STACK_H

#include "Common.h"

typedef struct STACK {
    Object object;

    void *(*top)(void *);

    void *(*pop)(void *);

    int (*push)(void *, void *);

    int (*empty)(void *);
} Stack;

int StackEmpty(void *v) {
    return ((Stack *) v)->empty(v);
}

void *StackTop(void *v) {
    return ((Stack *) v)->top(v);
}

int StackPush(void *v, void *x) {
    return ((Stack *) v)->push(v, x);
}

void *StackPop(void *v) {
    return ((Stack *) v)->pop(v);
}

#endif //CUTILITY_STACK_H
