#include <stdio.h>
#include "ArrayList.h"
#include "LinkedList.h"

void outputString(void *item) {
    printf("%s\n", (char *) item);
}

int main() {
    ArrayList *arrayList = InitArrayList(10);
    LinkedList *linkedList = InitLinkedList();

    List *list = (List *) arrayList;
    ArrayListInsert(arrayList, 0, "ArrayList Source Function");
    ListInsert(list, 1, "Common Function");
    ForEach(list, outputString);
    ListFree(list);

    list = (List *) linkedList;
    LinkedListInsert(linkedList, 0, "LinkedList Source Function");
    ListInsert(list, 1, "Common Function");
    ForEach(list, outputString);
    ListFree(list);

    return 0;
}