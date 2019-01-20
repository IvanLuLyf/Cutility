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
    while (p != NULL) {
        q = p;
        p = p->next;
        free(q);
    }
    free(v);
}

void LinkedListInfo() {
    printf("LinkedList\n");
}

char *LinkedListToString() {
    return "LinkedList";
}

LinkedList *InitLinkedList() {
    LinkedList *v;
    v = malloc(sizeof(LinkedList));
    v->head.next = NULL;
    v->length = 0;
    v->parent.insert = (int (*)(void *, int, void *)) LinkedListInsert;
    v->parent.delete = (int (*)(void *, int)) LinkedListDelete;
    v->parent.get = (void *(*)(void *, int)) LinkedListGet;
    v->parent.locate = (int (*)(void *, void *)) LinkedListLocate;
    v->parent.for_each = (void (*)(void *, void (*)(void *))) LinkedListForEach;
    v->parent.free_self = (void (*)(void *)) FreeLinkedList;
    v->parent.object.info = LinkedListInfo;
    v->parent.object.toString = LinkedListToString;
    return v;
}

#endif //CUTILITY_LINKEDLIST_H
