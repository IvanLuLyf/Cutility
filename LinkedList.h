//
// Created by IvanLu on 2019/1/20.
//

#ifndef CUTILITY_LINKEDLIST_H
#define CUTILITY_LINKEDLIST_H

#include "List.h"

typedef struct LINKED_NODE {
    void *data;
    struct LINKED_NODE *next;
} LinkedNode;

typedef struct LINKED_LIST {
    List parent;
    LinkedNode head;
    int length;
} LinkedList;

void *LinkedListGet(LinkedList *v, int pos) {
    int i = 0;
    LinkedNode *p = &v->head;
    if (pos < 0 || pos > v->length) {
        fprintf(stderr, "Invalid Position\n");
        return NULL;
    }
    while (p != NULL && i < pos + 1) {
        p = p->next;
        i++;
    }
    if (p != NULL) {
        return p->data;
    }
    return NULL;
}

int LinkedListSet(LinkedList *v, int pos, void *x) {
    int i = 0;
    LinkedNode *p = &v->head;
    if (pos < 0 || pos > v->length) {
        fprintf(stderr, "Invalid Position\n");
        return 0;
    }
    while (p != NULL && i < pos + 1) {
        p = p->next;
        i++;
    }
    if (p != NULL) {
        p->data = x;
        return 1;
    }
    return 0;
}

int LinkedListLocate(LinkedList *v, void *x) {
    int i = 0;
    LinkedNode *p = v->head.next;
    while (p != NULL) {
        if (p->data == x) {
            return i;
        }
        i++;
        p = p->next;
    }
    return -1;
}

int LinkedListInsert(LinkedList *v, int pos, void *x) {
    int i = 0;
    LinkedNode *p = &v->head, *q;
    if (pos < 0 || pos > v->length) {
        fprintf(stderr, "Invalid Position\n");
        return 0;
    }
    while (p != NULL && i < pos) {
        p = p->next;
        i++;
    }
    if (p != NULL) {
        q = (LinkedNode *) malloc(sizeof(LinkedNode));
        q->data = x;
        q->next = p->next;
        p->next = q;
        v->length++;
        return 1;
    }
    return 0;
}

int LinkedListDelete(LinkedList *v, int pos) {
    int i = 0;
    LinkedNode *p = &v->head, *q;
    if (pos < 0 || pos > v->length) {
        fprintf(stderr, "Invalid Position\n");
        return 0;
    }
    while (p != NULL && i < pos) {
        p = p->next;
        i++;
    }
    if (p != NULL && p->next != NULL) {
        q = p->next;
        p->next = q->next;
        free(q);
        v->length--;
        return 1;
    }
    return 0;
}

void LinkedListForEach(LinkedList *v, void (*op)(void *)) {
    LinkedNode *p = v->head.next;
    while (p != NULL) {
        op(p->data);
        p = p->next;
    }
}

void FreeLinkedList(LinkedList *v) {
    LinkedNode *p = v->head.next, *q;
    Object *object = NULL;
    while (p != NULL) {
        q = p;
        object = (Object *) (q->data);
        if (object->free_self != NULL) {
            object->free_self(object);
        }
        p = p->next;
        free(q);
    }
    free(v);
}

void LinkedListInfo() {
    printf("LinkedList\n");
}

char *LinkedListToString(void *object) {
    LinkedList *list = (LinkedList *) object;
    char *res = (char *) malloc(sizeof(char) * 50 * list->length);
    char *p = res;
    p[0] = '[';
    p++;
    ForEach(list, lambda(void, (void* item){
            sprintf(p, "%s,", parseString(item));
            while (*p!=0)p++;
    }));
    *(p - 1) = ']';
    *p = '\0';
    return res;
}

LinkedList *LinkedListFilter(LinkedList *v, int (*func)(void *));

LinkedList *LinkedListMap(LinkedList *v, void *(*func)(void *));

LinkedList *InitLinkedList() {
    LinkedList *v;
    v = malloc(sizeof(LinkedList));
    v->head.next = NULL;
    v->length = 0;
    v->parent.insert = (int (*)(void *, int, void *)) LinkedListInsert;
    v->parent.delete = (int (*)(void *, int)) LinkedListDelete;
    v->parent.get = (void *(*)(void *, int)) LinkedListGet;
    v->parent.set = (int (*)(void *, int, void *)) LinkedListGet;
    v->parent.locate = (int (*)(void *, void *)) LinkedListLocate;
    v->parent.for_each = (void (*)(void *, void (*)(void *))) LinkedListForEach;
    v->parent.filter = (void *(*)(void *, int (*)(void *))) LinkedListFilter;
    v->parent.map = (void *(*)(void *, void *(*)(void *))) LinkedListMap;
    v->parent.object.free_self = (void (*)(void *)) FreeLinkedList;
    v->parent.object.info = LinkedListInfo;
    v->parent.object.toString = LinkedListToString;
    return v;
}

LinkedList *LinkedListFilter(LinkedList *v, int (*func)(void *)) {
    LinkedList *res = InitLinkedList();
    LinkedNode *p, *q;
    p = &res->head;
    ForEach(v, lambda(void, (void* item){
            if (func(item)){
            q = (LinkedNode*)malloc(sizeof(LinkedNode));
            q->data = item;
            p->next = q;
            p =q;
    }
    }));
    p->next = NULL;
    return res;
}


LinkedList *LinkedListMap(LinkedList *v, void *(*func)(void *)) {
    LinkedList *res = InitLinkedList();
    LinkedNode *p, *q;
    p = &res->head;
    ForEach(v, lambda(void, (void* item){
            if (func(item)){
            q = (LinkedNode*)malloc(sizeof(LinkedNode));
            q->data = func(item);
            p->next = q;
            p =q;
    }
    }));
    p->next = NULL;
    return res;
}

#endif //CUTILITY_LINKEDLIST_H
