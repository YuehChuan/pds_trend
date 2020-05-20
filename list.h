#ifndef TREND_CLASSIFICATION_LIST_H
#define TREND_CLASSIFICATION_LIST_H
//typedef struct node Node;
//typedef struct list list;


typedef struct node {
    int data;
    struct node * next;
}Node;

typedef struct list {
    Node * head;
    int size;
}List;


List* makelist();
void add(int data, List* list);
void delete(int data, List* list);
void display(List* list);
void reverse(List* list);
void destroy(List* list);

#endif //TREND_CLASSIFICATION_LIST_H
