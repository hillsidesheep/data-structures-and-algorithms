#include<stdio.h>
#include<stdlib.h>


typedef int elem;

typedef struct listNode{
    elem element; 
    struct listNode *prev;
    struct listNode *next;
}listNode;

void initNode(listNode *head){
    head->next = head->prev = NULL;
}

_Bool insertList(listNode *head, elem element, int pos){
    if(pos < 1) return 0;
    while(--pos){
        head = head->next; 
        if(head == NULL) return 0;
        // printf("%d\n", pos);
    }
    // printf("%d\n", pos);
    listNode *node = malloc(sizeof(listNode));
    if(node == NULL) return 0;
    node->element = element;
    node->next = head->next;
    node->prev = head;
    node->prev->next = node;    
    if(node->next){
        node->next->prev = node;
    }
    return 1;
}

_Bool deleteList(listNode *head, int pos){
    if(pos < 1) return 0;
    while(--pos){
        head = head->next;
        if(head->next == NULL) return 0;
    }
    listNode *temp = head->next;
    head->next = temp->next;
    if(temp->next) temp->next->prev = head; 
    free(temp);
    return 1;
}

_Bool printList(listNode *head){
    do{
        head = head->next;
        printf("%d->", head->element);
    }while(head->next != NULL);
    printf("\n");
    do{
        printf("%d->", head->element);
        head = head->prev;
    }while(head->prev != NULL);
    printf("\n");
    return 1;
}

int main(){
    listNode head;
    initNode(&head);
    for(int i = 1; i<=5; ++i){
        if(!insertList(&head, 100*i, i)) printf("Failure: %d\n",i);
    }
    if(!printList(&head)) printf("Failure\n");
    int pos = 1;
    if(!insertList(&head, 100*pos, pos)) printf("Failure: %d\n",pos);
    if(!printList(&head)) printf("Failure\n");
    pos = 10;
    if(!deleteList(&head, pos)) printf("Failure: %d\n",pos);
    if(!printList(&head)) printf("Failure\n");

    return 0;
}