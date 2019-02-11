#include <stdio.h>
#include <mem.h>
#include "ArrayList.h"
#include "LinkedList.h"
#include "ArrayStack.h"

typedef struct STUDENT {
    Object parent;
    int id;
    char name[10];
} Student;

char *StudentToString(void *s) {
    Student *student = (Student *) s;
    char *result = malloc(sizeof(char) * 60);
    sprintf(result, "{\"id\":%d,\"name\":\"%s\"}", student->id, student->name);
    return result;
}

void freeStudent(void *object) {
    Student *student = (Student *) object;
    printf("%s be killed\n", student->name);
    free(object);
}

Student *newStudent(int id, char *name) {
    Student *student = (Student *) malloc(sizeof(Student));
    student->parent.toString = StudentToString;
    student->parent.free_self = freeStudent;
    student->id = id;
    strcpy(student->name, name);
    return student;
}

int main() {
    /*
    ArrayList *list = InitArrayList(50);
    ArrayListInsert(list,0,IntVal(1));
    ArrayListAppend(list, IntVal(10));
    ArrayListInsertMany(list, 7,
                          newStudent(1, "Ivan"),
                          newStudent(2, "Andy"),
                          newStudent(3, "Bob"),
                          newStudent(4, "Clara"),
                          newStudent(5, "Cindy"),
                          newStudent(6, "Dave"),
                          newStudent(7, "David")
    );
    ForEach(list, lambda(void, (void* item){
            printf("%s\n", parseString(item));
    }));
    printf("--------------\n");
    ForEach(ArrayListFilter(list,lambda(int,(void* item){
            Student* student = (Student*)item;
            return student->name[0] == 'C';
    })), lambda(void, (void* item){
            printf("%s\n", parseString(item));
    }));
     */
    /*
    ArrayStack *stack = InitArrayStack();
    printf("%d\n", ArrayStackEmpty(stack));
    ArrayStackPush(stack, "test");
    printf("%d\n", ArrayStackEmpty(stack));
    printf("%s\n", (char *) ArrayStackTop(stack));
    printf("%s\n", (char *) ArrayStackPop(stack));
    printf("%d\n", ArrayStackEmpty(stack));
     */
    List *list = (List *) InitLinkedList();
    ListInsert(list, 0, newStudent(1, "Ivan"));
    ListInsert(list, 0, newStudent(2, "Andy"));
    ListInsert(list, 0, newStudent(3, "Bob"));
    ListInsert(list, 0, newStudent(4, "Clara"));
    ListInsert(list, 0, newStudent(5, "Cindy"));
    ListInsert(list, 0, newStudent(6, "Dave"));
    ListInsert(list, 0, newStudent(7, "David"));
    ForEach(ListFilter(list, lambda(int, (void* item){
            Student* student = (Student*)item;
            return student->name[0] == 'C';
    })), lambda(void, (void* item){
            printf("%s\n", parseString(item));
    }));
    List *m = (List *) ListMap(list, lambda(void*, (void* item){
            Integer* res = IntVal(((Student*)item)->id);
            return res;
    }));
    ForEach(m, lambda(void, (void* item){
            printf("%s\n", parseString(item));
    }));
    Free(m);
    printf("------\n");
    Free(list);
    return 0;
}