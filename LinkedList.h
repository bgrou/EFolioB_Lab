#ifndef LINKEDLIST
#define LINKEDLIST
#include <malloc.h>
typedef void(*CallbackFree)(void *);
typedef int (*ComparisonFunction)(void*, int);
typedef struct node {
    void* data;
    struct node * next;
} Node;
typedef struct list {
    int data_size;
    int count;
    Node* head;
    Node* tail;
    CallbackFree callback_free;
} List;
typedef void(*CallbackFree)(void *);
void free_node_data(CallbackFree callback_free, void* data);
void list_push(List* list, void* data);
void list_destroy(List* list);
void* list_get(List* list, int index);
List* list_create(CallbackFree callback_free, int data_size);
void list_remove(List* list, int id, ComparisonFunction compare);
#endif //LINKEDLIST
