#include <stdio.h>
#include <stdlib.h>

#define initMaxsize 10

typedef int Elem;

typedef struct{
    Elem *data;
    int capacity;
    int length; // the number of elements
} SeqList;

_Bool initList(SeqList *list)
{
    list->data = (Elem *)malloc(sizeof(Elem) * initMaxsize);
    if (list->data == NULL)
        return 0;
    else{
        list->capacity = initMaxsize;
        list->length = 0;
        return 1;
    }
}

_Bool insertList(SeqList *list, int pos, Elem value)
{
    if (pos < 1 || pos > list->length + 1)
        return 0;

    if (list->length == list->capacity){
        int newCapacity = list->capacity + (list->capacity >> 1);
        Elem *tem = (Elem *)realloc(list->data, sizeof(Elem)*newCapacity);
        if(tem != NULL){
            list->data = tem;
            list->capacity = newCapacity;
        }
        else{
            return 0;
        } 
    }

    for (int i = list->length; i > pos - 1; --i)
    {
        list->data[i] = list->data[i - 1];
    }
    list->data[pos - 1] = value;
    list->length++;
    return 1;
}

int getPos(SeqList *list, Elem value){
    for(int i = 0; i < list->length; ++i){
        if(list->data[i] == value) return i + 1;
    }
    return -1;
}

Elem *getValue(SeqList *list, int pos){
    if(pos < 1 || pos > list->length) return NULL;
    return &list->data[pos - 1];
}

_Bool delletList(SeqList *list, int pos){
    if(pos < 1 || pos > list->length) return 0;
    for(int i = pos - 1; i < list->length - 1; ++i){
        list->data[i] = list->data[i + 1];
    }
    list->length--;
    return 1;
}

void printList(SeqList *list)
{   
    printf("list element:");
    if(list->length == 0) printf("NULL\n");
    else{
        for (int i = 0; i < list->length; ++i)
        {
            printf("%d  ", list->data[i]);
        }
        printf("\n");
    }
}

int main()
{
    SeqList list;

    if (initList(&list)){
        printf("list element:");
        printList(&list);

        printf("----------------------------------------------------------\n");

        for(int i = 0; i < list.capacity - 1; ++i){
            if (!(insertList(&list, i + 1, 10 * i))) printf("Failure\n");
        }

        if (!(insertList(&list, 8, 777))) printf("Failure\n");
        printf("----------------------------------------------------------\n");

        printList(&list);
        printf("list capacity: %d\nlist length: %d\n", list.capacity, list.length);
        printf("----------------------------------------------------------\n");

        if(!(insertList(&list, 5, 666))) printf("Failure\n");
        printList(&list);
        printf("list capacity: %d\nlist length: %d\n", list.capacity, list.length);
        printf("----------------------------------------------------------\n");
        
        if(delletList(&list, getPos(&list, *getValue(&list, 5)))){
            printList(&list);
            printf("list capacity: %d\nlist length: %d\n", list.capacity, list.length);
        }
    }

    return 0;
}