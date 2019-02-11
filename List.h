//
// Created by IvanLu on 2019/1/20.
//

#ifndef CUTILITY_LIST_H
#define CUTILITY_LIST_H

#include "Common.h"

typedef struct LIST {
    Object object;

    void *(*get)(void *, int);

    int (*set)(void *, int, void *);

    int (*locate)(void *, void *);

    int (*insert)(void *, int, void *);

    int (*delete)(void *, int);

    void (*for_each)(void *, void (*)(void *));

    void *(*filter)(void *, int (*)(void *));

    void *(*map)(void *, void *(*)(void *));
} List;

void *ListGet(void *list, int i) {
    return ((List *) list)->get(list, i);
}

int ListSet(void *list, int i, void *x) {
    return ((List *) list)->set(list, i, x);
}

int ListLocate(void *list, void *x) {
    return ((List *) list)->locate(list, x);
}

int ListInsert(void *list, int i, void *x) {
    return ((List *) list)->insert(list, i, x);
}

int ListDelete(void *list, int i) {
    return ((List *) list)->delete(list, i);
}

void ForEach(void *list, void (*op)(void *)) {
    ((List *) list)->for_each(list, op);
}

int ListCountIf(void *v, int (*func)(void *)) {
    int i = 0;
    ForEach(v, lambda(void, (void* item){
            if (func(item)) i++;
    }));
    return i;
}

List *ListFilter(void *v, int (*func)(void *)) {
    return ((List *) v)->filter(v, func);
}

List *ListMap(void *v, void *(*func)(void *)) {
    return ((List *) v)->map(v, func);
}

#endif //CUTILITY_LIST_H
