#include "LinkedList.h"

void free_node_data(CallbackFree callback_free, void* data) {
    if(callback_free != NULL) {
        callback_free(data);
    } else {
        free(data);
    }
}

List* list_create(CallbackFree callback_free, int data_size) {
    List* list = (List*)malloc(sizeof(List));
    list->callback_free = callback_free;
    list->data_size = data_size;
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void list_destroy(List* list){
    Node* current_node = list->head;
    while(current_node != NULL) {
        list->head = current_node->next;
        free_node_data(list->callback_free, current_node->data);
        free(current_node);
        current_node = list->head;
    }
    free(list);
}

void list_push(List* list, void* data) {
    Node* node = malloc(sizeof(Node));
    node->data = data;
    if(list->head == NULL) {
        list->head = node;
    } else {
        list->tail->next = node;
    }
    list->tail = node;
    list->tail->next = NULL;
    list->count++;
}

void* list_get(List* list, int index) {
    int i;
    Node* current_node = list->head;
    if(index < 1 || index > list->count) {
        return NULL;
    }
    for(i = 0; i < index - 1; i++) {
        current_node = current_node->next;
    }
    return current_node->data;
}

void list_remove(List* list, int id, ComparisonFunction compare) {
    if (list == NULL || list->head == NULL) {
        return;
    }
    if (compare(list->head->data, id)) {
        Node* target_node = list->head;
        list->head = target_node->next;
        if (list->head == NULL) {
            list->tail = NULL;
        }
        free_node_data(list->callback_free, target_node->data);
        free(target_node);
        return;
    }
    Node* current_node = list->head;
    Node* previous_node = NULL;
    while (current_node != NULL && !compare(current_node->data, id)) {
        previous_node = current_node;
        current_node = current_node->next;
    }
    if (current_node == NULL) {
        return;
    }
    if (current_node == list->tail) {
        list->tail = previous_node;
    }
    previous_node->next = current_node->next;
    free_node_data(list->callback_free, current_node->data);
    free(current_node);
}