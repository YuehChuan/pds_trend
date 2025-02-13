#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/*
struct node {
    int data;
    struct node * next;
};

struct list {
    Node * head;
    int size;
};
*/

Node * createnode(int data);

Node * createnode(int data){
    Node * newNode = malloc(sizeof(Node));
    if (!newNode) {
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

List* makelist(){
    List * list = malloc(sizeof(List));
    if (!list) {
        return NULL;
    }
    list->head = NULL;
    list->size = 0;
    return list;
}

void  display(List * list) {
    Node * current = list->head;
    if(list->head == NULL)
        return ;

    for(; current != NULL; current = current->next) {
        printf("%d\n", current->data);
    }
    printf("list size: %d\n", list->size);
}

void add(int data, List * list){
    Node * current = NULL;
    if(list->head == NULL){
        list->head = createnode(data);
        list->size +=1;
    }
    else {
        current = list->head;
        while (current->next!=NULL){
            current = current->next;
        }
        current->next = createnode(data);
        list->size +=1;

    }
}

void delete(int data, List * list){
    Node * current = list->head;
    Node * previous = current;
    while(current != NULL){
        if(current->data == data){
            previous->next = current->next;
            if(current == list->head)
                list->head = current->next;
            free(current);
            list->size -=1;
            return;
        }
        previous = current;
        current = current->next;
    }
}

void reverse(List * list){
    Node * reversed = NULL;
    Node * current = list->head;
    Node * temp = NULL;
    while(current != NULL){
        temp = current;
        current = current->next;
        temp->next = reversed;
        reversed = temp;
    }
    list->head = reversed;
}

void destroy(List * list){
    Node * current = list->head;
    Node * next = current;
    while(current != NULL){
        next = current->next;
        free(current);
        current = next;
    }
    free(list);
}
