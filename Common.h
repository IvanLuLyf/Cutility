//
// Created by IvanLu on 2019/1/20.
//

#ifndef CUTILITY_COMMON_H
#define CUTILITY_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define DEF_ARG(name, def_val) ((#name[0]) ? (name + 0) : def_val)

typedef struct OBJECT {
    void (*info)();

    char *(*toString)();
} Object;

void Info(void *object) {
    ((Object *) object)->info();
}

char *parseString(void *object) {
    return ((Object *) object)->toString();
}

#endif //CUTILITY_COMMON_H
