#include<stdio.h>
#include<stdlib.h>

typedef int elem;

typedef struct listNode{
    elem element; 
    struct listNode *next;
}listNode;

void initNode(listNode *head){
    head->next = NULL;
}

_Bool insertList(listNode *head, elem element, int pos){
    if(pos < 1) return 0;
    while(--pos){
        head = head->next; 
        //因为head意思是前驱结点，所以这个head->next才是真正的要操作的放置的位置。 
        // printf("%p\n", head);
        //因为最多只能给链表尾部再挂上一个值，而前驱结点为NULL,
        //相当于要给链表尾部的尾部之后的位置挂上一个值，所以肯定操作超出范围了
        if(head == NULL) return 0;
        // printf("%d\n", pos);
    }
    // printf("%d\n", pos);
    listNode *temp = malloc(sizeof(listNode));
    if(temp == NULL) return 0;
    temp->element = element;
    temp->next = head->next;
    head->next = temp;
    
    return 1;
}

_Bool deleteList(listNode *head, int pos){
    if(pos < 1) return 0;
    while(--pos){
        head = head->next;
        //由于head是前驱结点，所以head->next表示要删除的数，这个数为NULL,所以返回，操作越界了
        if(head->next == NULL) return 0;
    }
    listNode *temp = head->next;
    head->next = head->next->next;
    free(temp);
    return 1;
}

elem *getList(listNode *head, int pos){
    if(pos < 1) return NULL;
    while(--pos){
        head = head->next;
        if(head == NULL) return NULL;
    }
    return &head->next->element;
}

int findList(listNode *head, elem element){
    listNode *p = head->next;
    int i = 1;
    while(p != NULL){
        if(p->element == element) return i;
        p = p->next;
        ++i;
    }
    return -1;
}

void printList(listNode *head){
    head = head->next;
    while(head != NULL){
        printf("%d->", head->element);
        head = head->next;
    }
    printf("\n");
}

int main(){
    listNode head;
    initNode(&head);
    for(int i = 1; i <= 5; ++i){
        if(!insertList(&head, 100*i, i)) printf("Failure: %d\n",i);
    }
    printList(&head);
    int pos = 1;
    if(!insertList(&head, 100*pos, pos)) printf("Failure: %d\n",pos);
    printList(&head);
    // pos = 10;
    if(!deleteList(&head, pos)) printf("Failure: %d\n",pos);
    printList(&head);
    pos = 10;
    if(getList(&head, pos) == NULL) printf("Failure\n");
    else printf("%d\n", *getList(&head, pos));
    printf("%d\n", findList(&head, 50));

    return 0;
}